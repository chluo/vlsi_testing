/* Constants */

#define TRUE  1
#define FALSE 0

#define LOGIC_0  0
#define LOGIC_1  1
#define LOGIC_X  2

#define MAX_GATE_FANIN   2
#define MAX_PATTERNS     100000
#define MAX_GATES	       100000
#define MAX_PO		       2000
#define MAX_PI		       2000
#define MAX_FAULTS	     1000000
#define WORD_SIZE        32

/* signal values */
#define UNDEFINED     -1
#define LOGIC_0        0
#define LOGIC_1        1
#define LOGIC_X        2

/* redefined signal values */
#define MY_UNDEFINED   0
#define MY_LOGIC_0     1
#define MY_LOGIC_1     2
#define MY_LOGIC_X     3

/* Number of patterns run in parallel */ 
#define N_PARA      16

/* Data Structures */

typedef enum stuck_value_enum stuck_val_t;
enum stuck_value_enum {
    S_A_0, S_A_1
};

typedef enum gate_type_enum gate_type_t;
enum gate_type_enum {
  AND, OR, NAND, NOR, INV, BUF, PO_GND, PO_VCC, PI, PO, UNKNOWN
};

typedef struct pattern_struct pattern_t;
struct pattern_struct {
  int len;                          /* num. of pattern to be simulated */
  unsigned int *in[MAX_PATTERNS];   /* array of 3 value input patterns */
  unsigned int *out[MAX_PATTERNS];  /* corresponding array of 3 value output patterns */
};

typedef struct fault_list_struct fault_list_t;  /* linked list of faults */
struct fault_list_struct {

  int gate_index;        /* index of gate where fault is */
  int input_index;       /* (== -1) if fault at gate output */
                         /* (>= 0)  points to gate input where the fault is */
  stuck_val_t type;      /* type of stuck-at fault */
  fault_list_t *next;    /* next fault in list (NULL ptr if end of list) */

};

typedef struct gate_struct gate_t;
struct gate_struct {
  char *name;
  int index;                            /* set equal to index in ckt.gate[id] array */
  gate_type_t type;                     /* type of gate */
  int fanin[MAX_GATE_FANIN];            /* array of indices of fanin gates */
  int num_fanout;                       /* number of fanout's */
  int *fanout;                          /* array of indices of fanout gates */
  unsigned int in_val[MAX_GATE_FANIN];  /* store input values of gate for N_PARA patterns */
  unsigned int out_val;                 /* store output values of gate for N_PARA patterns */
  unsigned int out_ff;                  /* fault free output values for the current pattern */

  /* fault dropping flags: for two-input gates only */
  int fdrop_in0;                        /* fault dropping flag for input 0
                                           -1: no fault dropping; 
                                            0: drop s-a-0 fault 
                                            1: drop s-a-1 fault */
  int fdrop_in1;                        /* fault dropping flag for input 1
                                           -1: no fault dropping; 
                                            0: drop s-a-0 fault 
                                            1: drop s-a-1 fault */
  int fdrop_out;                        /* fault dropping flag for output 
                                           -1: no fault dropping; 
                                            0: drop s-a-0 fault 
                                            1: drop s-a-1 fault */
  int thing;                            /* mask indicating which patterns detected 
                                           the fault on the gate output */
};

typedef struct circuit_struct circuit_t;
struct circuit_struct {
  int ngates;                 /* number of gates in circuit */
  int npi;                    /* number of primary inputs */
  int npo;                    /* number of primary outputs */
  int *pi;                    /* array of indices of PI gates */
  int *po;                    /* array of indices of PO gates */
  gate_t *gate;               /* array of gates */
};
