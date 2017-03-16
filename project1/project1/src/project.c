#include "project.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* Macro Definitions */
#define BIT0_MASK 0x55555555
#define BIT1_MASK 0xaaaaaaaa

#define compute_INV(result,val) \
  { \
    result = ((val / 2) & BIT0_MASK) | ((val * 2) & BIT1_MASK); \
  }

#define compute_AND(result,val1,val2) \
  { \
    result = ((val1 | val2) & BIT0_MASK)  \
             | \
             ((val1 & val2) & BIT1_MASK) ;\
  } 

#define compute_OR(result,val1,val2) \
  { \
    result = ((val1 & val2) & BIT0_MASK)  \
             | \
             ((val1 | val2) & BIT1_MASK) ;\
  }

#define evaluate(gate_ptr) \
  { \
    switch( gate_ptr->type ) { \
    case PI: \
      break; \
    case PO: \
    case BUF: \
      gate_ptr->out_val = gate_ptr->in_val[0]; \
      break; \
    case PO_GND: \
      gate_ptr->out_val = BIT0_MASK; \
      break; \
    case PO_VCC: \
      gate_ptr->out_val = BIT1_MASK; \
      break; \
    case INV: \
      compute_INV(gate_ptr->out_val,gate_ptr->in_val[0]); \
      break; \
    case AND: \
      compute_AND(gate_ptr->out_val,gate_ptr->in_val[0],gate_ptr->in_val[1]); \
      break; \
    case NAND: \
      compute_AND(gate_ptr->out_val,gate_ptr->in_val[0],gate_ptr->in_val[1]); \
      compute_INV(gate_ptr->out_val,gate_ptr->out_val); \
      break; \
    case OR: \
      compute_OR(gate_ptr->out_val,gate_ptr->in_val[0],gate_ptr->in_val[1]); \
      break; \
    case NOR: \
      compute_OR(gate_ptr->out_val,gate_ptr->in_val[0],gate_ptr->in_val[1]); \
      compute_INV(gate_ptr->out_val,gate_ptr->out_val); \
      break; \
    default: \
      assert(0); \
    } \
  }

/*************************************************************************

Function:  three_val_fault_simulate

Purpose:  This function performs fault simulation on 3-valued input patterns.

pat.out[][] is filled with the fault-free output patterns corresponding to
the input patterns in pat.in[][].

Return:  List of faults that remain undetected.

*************************************************************************/

fault_list_t *three_val_fault_simulate(ckt,pat,undetected_flist)
  circuit_t    *ckt;
  pattern_t    *pat;
  fault_list_t *undetected_flist;
{
  int          p;                  /* looping variable for pattern number */
  int          i, j, k; 
  int          detected_flag;
  fault_list_t *fptr, *prev_fptr;

  /* loop through all pattern groups (N_PARA patterns per group) */
  for (p = 0/*, k = 0*/; p < pat->len; p += N_PARA/*, k += 1*/) {

    /* ----------------------------------------------------------------------
     * fault-free simulation
     * ------------------------------------------------------------------- */

    /* assign primary input values for pattern */ 
    for (i = 0; i < ckt->npi; i++) {
      gate_t *cur_pi = & (ckt->gate[ckt->pi[i]]);
      cur_pi->out_val = 0; 
      for (j = 0; j < N_PARA && p + j < pat->len; j++) 
        cur_pi->out_val |= (pat->in[p + j][i] + 1) << (2 * j);
    }
    /* evaluate all gates */
    for (i = 0; i < ckt->ngates; i++) {
      gate_t *cur_gate = & (ckt->gate[i]); 
      /* get gate input values */
      switch ( cur_gate->type ) {
        /* gates with no input terminal */
        case PI:
        case PO_GND:
        case PO_VCC:
          break;
        /* gates with one input terminal */
        case INV:
        case BUF:
        case PO:
          cur_gate->in_val[0] = ckt->gate[cur_gate->fanin[0]].out_val;
          break;
        /* gates with two input terminals */
        case AND:
        case NAND:
        case OR:
        case NOR:
          cur_gate->in_val[0] = ckt->gate[cur_gate->fanin[0]].out_val;
          cur_gate->in_val[1] = ckt->gate[cur_gate->fanin[1]].out_val;
          break;
        default:
          assert(0);
      }
      /* compute gate output value */
      evaluate(cur_gate);
      /* store fault free output values for each gate */ 
      cur_gate->out_ff = cur_gate->out_val; 
    }
    /* put fault-free primary output values into pat data structure */
    for (i = 0; i < ckt->npo; i++) {
      gate_t *cur_po = & (ckt->gate[ckt->po[i]]); 
      for (j = 0; j < N_PARA && p + j < pat->len; j++) {
        pat->out[p + j][i] = ((cur_po->out_val >> (2 * j)) & 3) - 1; 
      }
    }

    /* ----------------------------------------------------------------------
     * fault simulation
     * ------------------------------------------------------------------- */

    /* loop through all undetected faults */
    prev_fptr = (fault_list_t *)NULL;
    for (fptr = undetected_flist; fptr != (fault_list_t *)NULL; fptr=fptr->next) {
      /* loop through all pattern groups (N_PARA patterns per group) */
      detected_flag = FALSE;
      /* evaluate all gates */
      for (i = 0; i < ckt->ngates; i++) {
        gate_t *cur_gate = & (ckt->gate[i]); 
        /* assign fault-free output values of upstream gates */
        if (i < fptr->gate_index || cur_gate->type == PI) {
          cur_gate->out_val = cur_gate->out_ff;
        }
        /* faulty gate & downstream gates */
        if (i >= fptr->gate_index) {
          /* get gate input values */
          switch ( ckt->gate[i].type ) {
            /* gates with no input terminal */
            case PI:
            case PO_GND:
            case PO_VCC:
              break;
            /* gates with one input terminal */
            case INV:
            case BUF:
            case PO:
              cur_gate->in_val[0] = ckt->gate[cur_gate->fanin[0]].out_val;
              break;
            /* gates with two input terminals */
            case AND:
            case NAND:
            case OR:
            case NOR:
              cur_gate->in_val[0] = ckt->gate[cur_gate->fanin[0]].out_val;
              cur_gate->in_val[1] = ckt->gate[cur_gate->fanin[1]].out_val;
              break;
            default:
              assert(0);
          }
          /* check if faulty gate */
          if ( i == fptr->gate_index ) {
            /* check if fault at input */
            if ( fptr->input_index >= 0 ) {
              /* inject fault */
              if (fptr->type == S_A_0)
                cur_gate->in_val[fptr->input_index] = BIT0_MASK; 
              else 
                cur_gate->in_val[fptr->input_index] = BIT1_MASK; 
              /* compute gate output value */
              evaluate(cur_gate);
            }
            else { /* fault at output */
              /* inject fault */
              if (fptr->type == S_A_0)
                cur_gate->out_val = BIT0_MASK; 
              else 
                cur_gate->out_val = BIT1_MASK; 
            }
          }
          else { /* not faulty gate */
            /* compute gate output value */
            evaluate(cur_gate);
          }
        }
      }
      /* check if fault detected */
      for (i = 0; i < ckt->npo; i++) {
        gate_t *cur_po = & (ckt->gate[ckt->po[i]]); 
        for (j = 0; j < N_PARA && p + j < pat->len; j++) {
          if ( (((cur_po->out_val >> (2 * j)) & 3) == MY_LOGIC_0) && ( pat->out[p + j][i] == 1 )  
            || (((cur_po->out_val >> (2 * j)) & 3) == MY_LOGIC_1) && ( pat->out[p + j][i] == 0 ) ) {
            detected_flag = TRUE; break; 
          }
        }
        if (detected_flag) break; 
      }
      /* fault dropping */ 
      if ( detected_flag ) {
        /* remove fault from undetected fault list */
        if ( prev_fptr == (fault_list_t *)NULL ) {
          /* if first fault in fault list, advance head of list pointer */
          undetected_flist = fptr->next;
        }
        else { /* if not first fault in fault list, then remove link */
          prev_fptr->next = fptr->next;
        }
      }
      else { /* fault remains undetected, keep on list */
        prev_fptr = fptr;
      }
    }
  }
  return(undetected_flist);
}

