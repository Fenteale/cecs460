
#include "systemc.h"

SC_MODULE(MultTb){

/*
  sc_in<bool>  clk;
  sc_in<int>  din1;
  sc_in<int>  din2;
  sc_out <int>  dout;
*/
  sc_in<bool> clk;
  sc_signal<int> din1, din2, dout;
  void stim_gen();
  void check();

  SC_CTOR(MultTb){
   SC_THREAD(stim_gen);
   SC_METHOD(check);
   sensitive << clk.pos();
  }

};

void MultTb::stim_gen(){
  wait();
  din1 = 10;
  din2 = 10;
  wait();
  printf("[MON]:: %0d * %0d = %0d\n", din1.read(), din2.read(), dout.read());
  din1 = -10;
  din2 = 10;
  wait();
  printf("[MON]:: %0d * %0d = %0d\n", din1.read(), din2.read(), dout.read());

  sc_stop(); 
}


void MultTb::check(){
  if (dout != (din1 * din2)) {
    cout << "Output is NOT correct" << endl;
    sc_stop();
  }
  else {
    cout << "The output is correct" << endl;
    sc_stop(); 
  }
}