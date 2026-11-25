#include <systemc>
using namespace sc_core;
 
SC_MODULE(Timer) {
  sc_in<int> time_to_end{"end_time"}; //am vrut sa vad ce se intampla daca e diferit
  sc_event e;
 
  SC_CTOR(Timer) {
    SC_THREAD(run); 
  }
 
  void run() {
    wait(time_to_end, SC_NS);
    e.notify();
    std::cout << "done at:" << sc_time_stamp() << std::endl;
  }
};
 
int sc_main(int, char*[]) {
  sc_signal<int> end_time;
  end_time.write(68);

  Timer timer("timer");
  timer.time_to_end(end_time);
  sc_start(100, SC_NS);
  return 0;
}
