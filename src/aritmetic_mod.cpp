#include <systemc>
using namespace sc_core;
 
SC_MODULE(Calculator){
  sc_in<float> a{"a"};
  sc_in<float> b{"b"};
  sc_in<int> op{"op"};
  sc_out<float> result{"result"};

  SC_CTOR(Calculator){
    SC_METHOD(calculate);
    sensitive << a << b << op;
  };

  void calculate(){
    switch(op) {
      case 0:
        result.write(a+b);
        break;
      case 1:
        result.write(a-b);
        break;
      case 2:
        result.write(a*b);
        break;
      case 3:
        result.write(a/b);
        break;
    }
  }
};

int sc_main(int, char*[]) {
  sc_clock clk{"clk", 10, SC_NS};
  sc_signal<float> display_result, a, b;
  sc_signal<int> op;

  a.write(2.5);
  b.write(100.2);
  op.write(3);

  Calculator calculator("calculator");
  calculator.result(display_result);
  calculator.a(a);
  calculator.b(b);
  calculator.op(op);

  sc_start(50, SC_NS);

  std::cout<<a<<' '<<b<<' '<<op<<' '<<display_result;

  return 0;
}
