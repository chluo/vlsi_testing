module bist_hardware (
  clk, rst, bistmode, bistdone, bistpass, cut_scanmode, cut_sdi, cut_sdo
);

  input              clk          ;
  input              rst          ;
  input              bistmode     ;
  output             bistdone     ;
  output             bistpass     ;
  output             cut_scanmode ;
  output             cut_sdi      ;
  input              cut_sdo      ;

  // ======================================================================
  // Add your code here
  // ======================================================================
 
  /* Note: The number of scan cells in the DUT is 227 */ 

  // ----------------------------------------------------------------------
  // Signal list
  // ----------------------------------------------------------------------
  reg                bist_pg_lfsr_shift  ;  // Tell the pattern  generation  LFSR to shift by 1
  reg                bist_rc_lfsr_shift  ;  // Tell the Response compression LFSR to shift by 1
  reg  [ 15 : 0 ]    bist_pg_lfsr_r      ;  // Pattern  generation  LFSR seq elements
  reg  [ 15 : 0 ]    bist_rc_lfsr_r      ;  // Response compression LFSR seq elements
  reg  [ 15 : 0 ]    bist_sig_ff_r       ;  // Signatures of the fault-free response for all 2000 patterns
  reg                bist_ld_sig_ff      ;  // Tell the fault-free signature register to update
  wire [ 15 : 0 ]    bist_sig_ft         ;  // Signature of the potentially faulty response for the current pattern

  reg                bist_scan_cnt_inc   ;  // Tell the scan shift counter to increment
  reg                bist_patt_cnt_inc   ;  // Tell the pattern    counter to increment
  reg  [  7 : 0 ]    bist_scan_cnt_r     ;  // Scan shift counter
  reg  [ 10 : 0 ]    bist_patt_cnt_r     ;  // Pattern counter
  wire               bist_scan_cnt_ok    ;  // Scan shift counter reaches the wrap-around point
  wire               bist_patt_cnt_ok    ;  // Pattern counter    reaches the wrap-around point

  reg  [  1 : 0 ]    bist_ff_r           ;  // Fault-free controller state machine: 
                                            // Indicating if the current BIST is the fault-free case
  reg  [  2 : 0 ]    bist_st_r           ;  // Main state machine: 
                                            // Controlling the BIST process
  reg  [  2 : 0 ]    bist_st_nxt         ;  // Next state of the main state machine

  reg                bistdone            ;  // Asserted when the BIST result is available
  reg                bistpass            ;  // A 1 indicates the BIST is passed, otherwise failed
  reg                cut_scanmode        ;  // Scan mode select signal to the CUT

  // ----------------------------------------------------------------------
  // Parameters
  // ----------------------------------------------------------------------
  // Fault-free controller state machine states
  parameter    FF_RST        =  2'b00  ; // State after the first reset
  parameter    FF_FFY        =  2'b01  ; // Reach this state before the first BIST is done: 
                                         // Indicating this is the fault-free case
  parameter    FF_FFN        =  2'b11  ; // Remain in this sate after the first BIST is done: 
                                         // Indicating this is a potentially faulty case

  // Main state machine states
  parameter    BIST_IDLE     =  3'b000 ; // Idle state, waiting for the BIST mode initiating signal
  parameter    BIST_APLY     =  3'b001 ; // Shifting in a test pattern to the CUT
  parameter    BIST_CAPT     =  3'b011 ; // Capture cycle
  parameter    BIST_CHCK     =  3'b111 ; // Shifting out the response of the test pattern, and compressing the response
                                         // And shifting in the next pattern at the same time 
  parameter    BIST_EXIT     =  3'b110 ; // Finish the BIST by checking the signature 

  // ----------------------------------------------------------------------
  // LFSR's
  // ----------------------------------------------------------------------
  // 16-bit LFSR for pattern generation: x^16 + x^5 + x^4 + x^3 + 1 
  always @ ( posedge clk ) begin : pg_lfsr
    // Synchronous reset, active high 
    if ( rst ) begin 
      // Reset value makes sure the LFSR does not stuck at all-zero state
      // Synchronous reset, so it is okay to reset DFFs as 1
      bist_pg_lfsr_r <= 16'd1 ;
    end 
    else if ( bist_pg_lfsr_shift ) begin 
      bist_pg_lfsr_r [  0 ] <= bist_pg_lfsr_r [ 15 ]                         ;
      bist_pg_lfsr_r [  1 ] <= bist_pg_lfsr_r [  0 ]                         ;
      bist_pg_lfsr_r [  2 ] <= bist_pg_lfsr_r [  1 ]                         ;
      bist_pg_lfsr_r [  3 ] <= bist_pg_lfsr_r [  2 ] ^ bist_pg_lfsr_r [ 15 ] ;
      bist_pg_lfsr_r [  4 ] <= bist_pg_lfsr_r [  3 ] ^ bist_pg_lfsr_r [ 15 ] ;
      bist_pg_lfsr_r [  5 ] <= bist_pg_lfsr_r [  4 ] ^ bist_pg_lfsr_r [ 15 ] ;
      bist_pg_lfsr_r [  6 ] <= bist_pg_lfsr_r [  5 ]                         ;
      bist_pg_lfsr_r [  7 ] <= bist_pg_lfsr_r [  6 ]                         ;
      bist_pg_lfsr_r [  8 ] <= bist_pg_lfsr_r [  7 ]                         ;
      bist_pg_lfsr_r [  9 ] <= bist_pg_lfsr_r [  8 ]                         ;
      bist_pg_lfsr_r [ 10 ] <= bist_pg_lfsr_r [  9 ]                         ;
      bist_pg_lfsr_r [ 11 ] <= bist_pg_lfsr_r [ 10 ]                         ;
      bist_pg_lfsr_r [ 12 ] <= bist_pg_lfsr_r [ 11 ]                         ;
      bist_pg_lfsr_r [ 13 ] <= bist_pg_lfsr_r [ 12 ]                         ;
      bist_pg_lfsr_r [ 14 ] <= bist_pg_lfsr_r [ 13 ]                         ;
      bist_pg_lfsr_r [ 15 ] <= bist_pg_lfsr_r [ 14 ]                         ;
    end 
  end 

  // Connect the scan data input to the pattern generator
  assign cut_sdi = bist_pg_lfsr_r [ 15 ] ; 

  // 16-bit LFSR for response compression: x^16 + x^5 + x^4 + x^3 + 1 
  always @ ( posedge clk ) begin : rc_lfsr
    // Synchronous reset, active high 
    if ( rst ) begin 
      // Reset value makes sure the LFSR does not stuck at all-zero state
      // Synchronous reset, so it is okay to reset DFFs as 1
      bist_rc_lfsr_r <= 16'd1 ;
    end 
    else if ( bist_rc_lfsr_shift ) begin 
      bist_rc_lfsr_r [  0 ] <= bist_rc_lfsr_r [ 15 ] ^ cut_sdo               ;
      bist_rc_lfsr_r [  1 ] <= bist_rc_lfsr_r [  0 ]                         ;
      bist_rc_lfsr_r [  2 ] <= bist_rc_lfsr_r [  1 ]                         ;
      bist_rc_lfsr_r [  3 ] <= bist_rc_lfsr_r [  2 ] ^ bist_rc_lfsr_r [ 15 ] ;
      bist_rc_lfsr_r [  4 ] <= bist_rc_lfsr_r [  3 ] ^ bist_rc_lfsr_r [ 15 ] ;
      bist_rc_lfsr_r [  5 ] <= bist_rc_lfsr_r [  4 ] ^ bist_rc_lfsr_r [ 15 ] ;
      bist_rc_lfsr_r [  6 ] <= bist_rc_lfsr_r [  5 ]                         ;
      bist_rc_lfsr_r [  7 ] <= bist_rc_lfsr_r [  6 ]                         ;
      bist_rc_lfsr_r [  8 ] <= bist_rc_lfsr_r [  7 ]                         ;
      bist_rc_lfsr_r [  9 ] <= bist_rc_lfsr_r [  8 ]                         ;
      bist_rc_lfsr_r [ 10 ] <= bist_rc_lfsr_r [  9 ]                         ;
      bist_rc_lfsr_r [ 11 ] <= bist_rc_lfsr_r [ 10 ]                         ;
      bist_rc_lfsr_r [ 12 ] <= bist_rc_lfsr_r [ 11 ]                         ;
      bist_rc_lfsr_r [ 13 ] <= bist_rc_lfsr_r [ 12 ]                         ;
      bist_rc_lfsr_r [ 14 ] <= bist_rc_lfsr_r [ 13 ]                         ;
      bist_rc_lfsr_r [ 15 ] <= bist_rc_lfsr_r [ 14 ]                         ;
    end 
  end

  // The output of the response compression LFSR is the reponse signature
  assign bist_sig_ft = bist_rc_lfsr_r ;

  // ----------------------------------------------------------------------
  // Fault-free signature register 
  // ----------------------------------------------------------------------
  always @ ( posedge clk ) begin 
    // Should not reset at the beginning of each BIST
    bist_sig_ff_r <= bist_ld_sig_ff ? bist_rc_lfsr_r : bist_sig_ff_r ; 
  end 

  // ----------------------------------------------------------------------
  // Counters
  // ----------------------------------------------------------------------
  // Scan shift counter (0 - 226, 8 bits)
  assign bist_scan_cnt_ok = ( bist_scan_cnt_r == 8'd226 ) ;

  always @ ( posedge clk ) begin 
    if ( rst ) 
      bist_scan_cnt_r <= 8'd0 ;
    // Wrap around 
    else if ( bist_scan_cnt_ok && bist_scan_cnt_inc ) 
      bist_scan_cnt_r <= 8'd0 ;
    // Increment by 1 when scanning in or out
    else if ( bist_scan_cnt_inc )
      bist_scan_cnt_r <= bist_scan_cnt_r + 1 ;
    else 
      bist_scan_cnt_r <= bist_scan_cnt_r ;
  end 

  // Pattern counter (0 - 1999, 11 bits)
  assign bist_patt_cnt_ok = ( bist_patt_cnt_r == 11'd1999 ) ;

  always @ ( posedge clk ) begin 
    if ( rst ) 
      bist_patt_cnt_r <= 11'd0 ;
    // Wrap around 
    else if ( bist_patt_cnt_ok && bist_patt_cnt_inc ) 
      bist_patt_cnt_r <= 11'd0 ;
    // Increment by 1 when a pattern is captured into the CUT
    else if ( bist_patt_cnt_inc )
      bist_patt_cnt_r <= bist_patt_cnt_r + 1 ;
    else 
      bist_patt_cnt_r <= bist_patt_cnt_r ;
  end 

  // ----------------------------------------------------------------------
  // The fault-free controller state machine
  // ----------------------------------------------------------------------
  // Determine if the current BIST is the fault-free case
  
  /* Note: This part won't work if you put this on silicon.
   * You can never distinguish between the first reset and
   * other resets since all states are UNKNOWN (which can
   * be anything) during the first reset. I tried to make
   * it work but later found out it will never work no
   * matter what kind of state machine is used, as long
   * as the system asserts reset each time a new BIST is
   * initiated. */

  always @ ( posedge clk ) begin 
    // The first BIST is the fault-free case
    if ( rst ) 
      bist_ff_r <= FF_RST ; 
    else if ( bist_ff_r == FF_RST && bist_st_nxt == BIST_EXIT ) 
      bist_ff_r <= FF_FFY ;

    // Permanently set it to FF_FFN after the first BIST is done
    if ( bist_ff_r != FF_RST && bistdone ) 
      bist_ff_r <= FF_FFN ;
  end 

  // ----------------------------------------------------------------------
  // Main state machine 
  // ----------------------------------------------------------------------
  // Control the BIST process
  always @ ( * ) begin 
    // Default signal values
    bist_pg_lfsr_shift  =  1'b0      ; 
    bist_rc_lfsr_shift  =  1'b0      ;
    bist_scan_cnt_inc   =  1'b0      ;
    bist_patt_cnt_inc   =  1'b0      ;
    bist_ld_sig_ff      =  1'b0      ;
    bistdone            =  1'b0      ;
    bistpass            =  1'b0      ;
    cut_scanmode        =  1'b0      ;
    bist_st_nxt         =  BIST_IDLE ;

    // States
    case ( bist_st_r ) 

      BIST_IDLE : begin 
        bist_st_nxt = ( rst && bistmode ) ? BIST_APLY : bist_st_r ;
      end // BIST_IDLE

      BIST_APLY : begin 
        bist_pg_lfsr_shift = 1'b1 ;
        bist_scan_cnt_inc  = 1'b1 ;
        cut_scanmode       = 1'b1 ;
        bist_st_nxt        = bist_scan_cnt_ok ? BIST_CAPT : bist_st_r ;
      end // BIST_APLY

      BIST_CAPT : begin 
        bist_patt_cnt_inc  = 1'b1 ;
        bist_st_nxt        = BIST_CHCK ; 
      end // BIST_CAPT

      BIST_CHCK : begin 
        bist_rc_lfsr_shift = 1'b1 ;
        bist_pg_lfsr_shift = 1'b1 ;
        bist_scan_cnt_inc  = 1'b1 ;
        cut_scanmode       = 1'b1 ;
        if ( bist_scan_cnt_ok && bist_patt_cnt_ok ) 
          bist_st_nxt = BIST_EXIT ; 
        else if ( bist_scan_cnt_ok ) 
          bist_st_nxt = BIST_CAPT ; 
        else 
          bist_st_nxt = bist_st_r ;
      end // BIST_CHCK

      BIST_EXIT : begin 
        bist_ld_sig_ff = ( bist_ff_r == FF_FFY ) ;
        bistdone       = 1'b1      ; 
        bistpass       = ( bist_ff_r == FF_FFY || bist_sig_ft == bist_sig_ff_r ) ; 
      end // BIST_EXIT
    endcase 
  end 

  // State transition
  always @ ( posedge clk ) begin 
    if ( rst && bistmode ) 
      bist_st_r <= BIST_APLY   ; 
    else 
      bist_st_r <= bist_st_nxt ; 
  end 

endmodule  

module chip(clk,rst,pi,po,bistmode,bistdone,bistpass);
  input          clk;
  input          rst;
  input	 [34:0]  pi;
  output [48:0]  po;
  input          bistmode;
  output         bistdone;
  output         bistpass;

  wire           cut_scanmode,cut_sdi,cut_sdo;

  reg x;
  wire w_x;
  assign w_x = x;

  scan_cut circuit(bistmode,cut_scanmode,cut_sdi,cut_sdo,clk,rst,
         pi[0],pi[1],pi[2],pi[3],pi[4],pi[5],pi[6],pi[7],pi[8],pi[9],
         pi[10],pi[11],pi[12],pi[13],pi[14],pi[15],pi[16],pi[17],pi[18],pi[19],
         pi[20],pi[21],pi[22],pi[23],pi[24],pi[25],pi[26],pi[27],pi[28],pi[29],
         pi[30],pi[31],pi[32],pi[33],pi[34],
         po[0],po[1],po[2],po[3],po[4],po[5],po[6],po[7],po[8],po[9],
         po[10],po[11],po[12],po[13],po[14],po[15],po[16],po[17],po[18],po[19],
         po[20],po[21],po[22],po[23],po[24],po[25],po[26],po[27],po[28],po[29],
         po[30],po[31],po[32],po[33],po[34],po[35],po[36],po[37],po[38],po[39],
         po[40],po[41],po[42],po[43],po[44],po[45],po[46],po[47],po[48]);
  bist_hardware bist( clk,rst,bistmode,bistdone,bistpass,cut_scanmode,
                     cut_sdi,cut_sdo);
  
endmodule
