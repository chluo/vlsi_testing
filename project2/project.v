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

  //
  // Add your code here
  // 
  /* Note: The number of scan cells in the DUT is 227 */ 

  // 
  // Signal list
  //
  reg                bist_pg_lfsr_shift  ;  // Tell the pattern  generation  LFSR to shift by 1
  reg                bist_rc_lfsr_shift  ;  // Tell the Response compression LFSR to shift by 1
  reg  [ 15 : 0 ]    bist_pg_lfsr_r      ;  // Pattern  generation  LFSR seq elements
  reg  [ 15 : 0 ]    bist_rc_lfsr_r      ;  // Response compression LFSR seq elements
  reg  [ 15 : 0 ]    bist_sig_ff_r       ;  // Signatures of the fault-free response for all 2000 patterns
  reg  [ 15 : 0 ]    bist_sig_ft_r       ;  // Signature  of the faulty     response for the current pattern

  reg                bist_scan_cnt_inc   ;  // Tell the scan shift counter to increment
  reg                bist_patt_cnt_inc   ;  // Tell the pattern    counter to increment
  reg  [  7 : 0 ]    bist_scan_cnt_r     ;  // Scan shift counter
  reg  [ 10 : 0 ]    bist_patt_cnt_r     ;  // Pattern counter
  reg                bist_ff_r           ;  // State indicating the current test is the fault-free test
  reg  [  2 : 0 ]    bist_st_r           ;  // State controlling the test precedure

  reg                bistdone            ;  // Asserted when the BIST result is available
  reg                bistpass            ;  // A 1 indicates the BIST is passed, otherwise failed
  reg                cut_scanmode        ;  // Scan mode select signal to the CUT

  //
  // LFSR's
  //
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
  end : pg_lfsr

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
  end : rc_lfsr

  // 
  // Counters
  //
  // Scan shift counter (0 - 276, 8 bits)
  always @ ( posedge clk ) begin 
    if ( rst ) 
      bist_scan_cnt_r <= 8'd0 ;
    // Wrap around 
    else if ( bist_scan_cnt_r == 8'd276 ) 
      bist_scan_cnt_r <= 8'd0 ;
    // Increment by 1 when scanning in or out
    else if ( bist_scan_cnt_inc )
      bist_scan_cnt_r <= bist_scan_cnt_r + 1 ) ;
    else 
      bist_scan_cnt_r <= bist_scan_cnt_r ;
  end 

  // Pattern counter (0 - 1999, 11 bits)
  always @ ( posedge clk ) begin 
    if ( rst ) 
      bist_patt_cnt_r <= 11'd0 ;
    // Wrap around 
    else if ( bist_patt_cnt_r == 11'd1999 ) 
      bist_patt_cnt_r <= 11'd0 ;
    // Increment by 1 when a pattern is captured into the CUT
    else if ( bist_patt_cnt_inc )
      bist_patt_cnt_r <= bist_patt_cnt_r + 1 ) ;
    else 
      bist_patt_cnt_r <= bist_patt_cnt_r ;
  end 

  //
  // State machines 
  //
  // Determine if the current BIST is the fault-free case
  always @ ( posedge clk ) begin 
    // The first BIST is the fault-free case, so reset to 1
    if ( rst ) 
      bist_ff_r <= 1'b1 ; 
    // Permanently set it to 0 after the first BIST is done
    else if ( bist_done ) 
      bist_ff_r <= 1'b0 ;
  end 

  // Main state machine 

//*  // Previous unsynthesizable code
//*  //
//*  // Help tasks and functions
//*  //
//*  // Apply one scan pattern
//*  task bist_apply_pat ( input int i ) ; 
//*    // Initiate the scan mode
//*    @ ( posedge clk ) 
//*    cut_scanmode       <= 1'b1 ;
//*    bist_pg_lfsr_shift <= 1'b1 ; 
//*    // Scan in one pattern (277 cycles) 
//*    repeat ( 277 ) @ ( posedge clk ) 
//*    // Exit the scan mode
//*    cut_scanmode       <= 1'b0 ;
//*    bist_pg_lfsr_shift <= 1'b0 ; 
//*    // Capture 
//*    @ ( posedge clk ) 
//*    // Scan out (277 cycles) 
//*    cut_scanmode       <= 1'b1 ;
//*    bist_rc_lfsr_shift <= 1'b1 ; 
//*    repeat ( 277 ) @ ( posedge clk ) 
//*    // Scan-out complete
//*    cut_scanmode       <= 1'b0 ;
//*    bist_rc_lfsr_shift <= 1'b0 ; 
//*    // Store the signature(s)
//*    @ ( posedge clk ) begin 
//*      bist_sig_ft_r <= bist_rc_lfsr_r ;
//*      // Store the fault-free signature if it is the first test
//*      // The fist test is fault-free according to the project document
//*      if ( bist_ff_r ) 
//*        bist_sig_ff_r [ i ] <= bist_rc_lfsr_r ;
//*    end 
//*  endtask 
//*
//*  // Check the output signature against the fault-free one  
//*  function int bist_check_sig ( int i ) ;
//*    if ( bist_ff_r ) return 1 ; 
//*    if ( bist_sig_ft_r != bist_sig_ff_r [ i ] ) return 0 ; 
//*    else                                        return 1 ;
//*  endfunction 
//*
//*  // Evaluate the signature and output the result
//*  task bist_finish ( input int i ) ;
//*    @ ( posedge clk ) 
//*      bistdone <= 1'b1 ; 
//*    @ ( posedge clk ) 
//*      bistdone <= 1'b0 ; 
//*  endtask 
//*
//*  // 
//*  // Main routine 
//*  //
//*  initial begin 
//*    while ( 1 ) begin 
//*      // Synchronize the whole thing with clk 
//*      // Wait until the BIST mode is initiated (not sure if Verilog supports the wait keyword) 
//*      // When rst is asserted, the pattern generator is reset at the same time
//*      forever @ ( posedge clk ) begin 
//*        if ( bist_mode && rst ) begin 
//*          // Clear the output signals on reset
//*          bistdone     <= 1'b0 ; 
//*          bistpass     <= 1'b0 ; 
//*          cut_scanmode <= 1'b0 ;
//*          break ; 
//*        end 
//*      end // forever @ ( posedge clk ) 
//*
//*      // Apply 2000 pseudo-random scan patterns
//*      for ( int i = 0 ; i < 2000 ; i = i + 1 ) begin 
//*        // Apply a scan pattern and store the response signature
//*        bist_apply_pat ( i ) ;
//*        // BIST is passed only if all 2000 patterns get the correct response
//*        bistpass <= bistpass & ( bist_check_sig ( i ) ? 1'b1 : 1'b0 ) ;
//*      end // for
//*      // Evaluate the response signature and output the result
//*      bist_finish ( i ) ;
//*    end // while ( 1 ) 
//*  end // initial 

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
