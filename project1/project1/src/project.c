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
    int temp = (~val & ~(val >> 1)) & BIT0_MASK; \
    result = ~((temp | (temp << 1)) | val); \
  }

#define compute_AND(result,val1,val2) \
  { \
    result = ((val1 & BIT0_MASK) | (val2 & BIT0_MASK))  \
             | \
             ((val1 & BIT1_MASK) & (val2 & BIT1_MASK)) ;\
  } 

#define compute_OR(result,val1,val2) \
  { \
    result = ((val1 & BIT0_MASK) & (val2 & BIT0_MASK))  \
             | \
             ((val1 & BIT1_MASK) | (val2 & BIT1_MASK)) ;\
  }

#define evaluate(gate) \
  { \
    switch( gate.type ) { \
    case PI: \
      break; \
    case PO: \
    case BUF: \
      gate.out_val = gate.in_val[0]; \
      break; \
    case PO_GND: \
      gate.out_val = LOGIC_0; \
      break; \
    case PO_VCC: \
      gate.out_val = LOGIC_1; \
      break; \
    case INV: \
      compute_INV(gate.out_val,gate.in_val[0]); \
      break; \
    case AND: \
      compute_AND(gate.out_val,gate.in_val[0],gate.in_val[1]); \
      break; \
    case NAND: \
      compute_AND(gate.out_val,gate.in_val[0],gate.in_val[1]); \
      compute_INV(gate.out_val,gate.out_val); \
      break; \
    case OR: \
      compute_OR(gate.out_val,gate.in_val[0],gate.in_val[1]); \
      break; \
    case NOR: \
      compute_OR(gate.out_val,gate.in_val[0],gate.in_val[1]); \
      compute_INV(gate.out_val,gate.out_val); \
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
  int          p;  /* looping variable for pattern number */
  int          i;
  int          j; 
  fault_list_t *fptr, *prev_fptr;
  int          detected_flag;

  /*************************/
  /* fault-free simulation */
  /*************************/
  /* loop through all pattern groups (N_PARA patterns per group) */
  for (p = 0; p < pat->len; p += N_PARA) {
    /* printf("pattern #%d\n", p); */
    /* initialize all gate values to UNDEFINED */
    for (i = 0; i < ckt->ngates; i++) {
      ckt->gate[i].in_val[0] = 0;
      ckt->gate[i].in_val[1] = 0;
      ckt->gate[i].out_val   = 0;
    }
    /* assign primary input values for pattern */ 
    for (i = 0; i < ckt->npi; i++) {
      for (j = 0; j < N_PARA && p + j < pat->len; j++) {
        ckt->gate[ckt->pi[i]].out_val |= ((pat->in[p + j][i] & 3) == 0 ? LOGIC_0 : (pat->in[p + j][i] & 3) == 1 ? LOGIC_1 : LOGIC_X) << (2 * j);
      }
      /* printf ("pattern: %x\n", ckt->gate[ckt->pi[i]].out_val); */
    }
    /* evaluate all gates */
    for (i = 0; i < ckt->ngates; i++) {
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
          ckt->gate[i].in_val[0] = ckt->gate[ckt->gate[i].fanin[0]].out_val;
          break;
        /* gates with two input terminals */
        case AND:
        case NAND:
        case OR:
        case NOR:
          ckt->gate[i].in_val[0] = ckt->gate[ckt->gate[i].fanin[0]].out_val;
          ckt->gate[i].in_val[1] = ckt->gate[ckt->gate[i].fanin[1]].out_val;
          break;
        default:
          assert(0);
      }
      /* compute gate output value */
      evaluate(ckt->gate[i]);
    }
    /* put fault-free primary output values into pat data structure */
    for (i = 0; i < ckt->npo; i++) {
      for (j = 0; j < N_PARA && p + j < pat->len; j++) 
        pat->out[p + j][i] = ((ckt->gate[ckt->po[i]].out_val >> (2 * j)) & 3) == LOGIC_0 ? 0 :
                             ((ckt->gate[ckt->po[i]].out_val >> (2 * j)) & 3) == LOGIC_1 ? 1 : 2;
    }
  }

  /********************/
  /* fault simulation */
  /********************/

  /* loop through all undetected faults */
  prev_fptr = (fault_list_t *)NULL;
  for (fptr=undetected_flist; fptr != (fault_list_t *)NULL; fptr=fptr->next) {
    /* loop through all pattern groups (N_PARA patterns per group) */
    detected_flag = FALSE;
    for (p = 0; p < pat->len && !detected_flag; p += N_PARA) {
      /* initialize all gate values to UNDEFINED */
      for (i = 0; i < ckt->ngates; i++) {
        ckt->gate[i].in_val[0] = 0;
        ckt->gate[i].in_val[1] = 0;
        ckt->gate[i].out_val   = 0;
      }
      /* assign primary input values for pattern */ 
      for (i = 0; i < ckt->npi; i++) {
        for (j = 0; j < N_PARA && p + j < pat->len; j++) 
          ckt->gate[ckt->pi[i]].out_val |= ((pat->in[p + j][i] & 3) == 0 ? LOGIC_0 : (pat->in[p + j][i] & 3) == 1 ? LOGIC_1 : LOGIC_X) << (2 * j);
      }
      /* evaluate all gates */
      for (i = 0; i < ckt->ngates; i++) {
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
            ckt->gate[i].in_val[0] = ckt->gate[ckt->gate[i].fanin[0]].out_val;
            break;
          /* gates with two input terminals */
          case AND:
          case NAND:
          case OR:
          case NOR:
            ckt->gate[i].in_val[0] = ckt->gate[ckt->gate[i].fanin[0]].out_val;
            ckt->gate[i].in_val[1] = ckt->gate[ckt->gate[i].fanin[1]].out_val;
            break;
          default:
            assert(0);
        }
        /* check if faulty gate */
        if ( i == fptr->gate_index ) {
          /* check if fault at input */
          if ( fptr->input_index >= 0 ) {
            /* inject fault */
            if ( fptr->type == S_A_0 ) {
              ckt->gate[i].in_val[fptr->input_index] = BIT0_MASK;
            }
            else { 
              ckt->gate[i].in_val[fptr->input_index] = BIT1_MASK;
            }
            /* compute gate output value */
            evaluate(ckt->gate[i]);
          }
          else { /* fault at output */
            /* evaluate(ckt->gate[i]); */
            /* inject fault */
            if ( fptr->type == S_A_0 ) {
              ckt->gate[i].out_val = BIT0_MASK; 
            }
            else { /* S_A_1 */
              ckt->gate[i].out_val = BIT1_MASK;
            }
          }
        }
        else { /* not faulty gate */
          /* compute gate output value */
          evaluate(ckt->gate[i]);
        }
      }
      /* check if fault detected */
      for (i = 0; i < ckt->npo; i++) {
        for (j = 0; j < N_PARA && p + j < pat->len; j++) {
          /* printf ("%d, %d\n", (ckt->gate[ckt->po[i]].out_val >> (2 * j)) & 3, pat->out[p + j][i]); */
          if ( (((ckt->gate[ckt->po[i]].out_val >> (2 * j)) & 3) == LOGIC_0) && ( pat->out[p + j][i] == 1 ) ) {
            detected_flag = TRUE;             
            break; 
          }
          if ( (((ckt->gate[ckt->po[i]].out_val >> (2 * j)) & 3) == LOGIC_1) && ( pat->out[p + j][i] == 0 ) ) {
            detected_flag = TRUE;
            break; 
          }
        }
        if (detected_flag) break; 
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
  return(undetected_flist);
}
