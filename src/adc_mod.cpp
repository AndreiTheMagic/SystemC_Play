#include <systemc.h>
#include <algorithm>
#include <cmath>

SC_MODULE(ADC){
  sc_in<bool> clk;
  sc_in<double> analog_in;
  sc_out<sc_uint<10>> digital_out;

  const double vref = 3.3; //V

  void convert(){
      double vin = analog_in.read();
      double clamped = std::clamp(vin, 0.0, vref);
      int dig = static_cast<int>(std::floor((clamped / vref) * 1024.0));
      digital_out.write(static_cast<sc_uint<10>>(dig));
  }

  SC_CTOR(ADC){
      SC_METHOD(convert);
      sensitive << clk.pos();
      dont_initialize();
  }
};

SC_MODULE(AnalogGen){
  sc_out<double> an_out{"analog_out"};

  void generate() {
    //2.0 * 3.14159265358979323846;
    while(true){
      double wave = 1.65 + 1.65 * std::sin(2.0 * 3.14159265358979323846 * 1000.0 * sc_time_stamp().to_seconds());
      //offset de 1.65V + semnal sinusoidal +- 1.65V ( cu frecventa de 1kHz)
      an_out.write(wave);
      wait(sc_time(1, SC_US));
    }
  }

  SC_CTOR(AnalogGen){
    SC_THREAD(generate);
  }
};

int sc_main(int argc, char* argv[]) {
  sc_clock clk("clk", 50, SC_US); // face la 50us convert
  sc_signal<double> analog_sig("analog_sig");
  sc_signal<sc_uint<10>> digital_sig("digital_sig");

  AnalogGen gen("gen");
  gen.an_out(analog_sig);

  ADC adc("adc");
  adc.clk(clk);
  adc.analog_in(analog_sig);
  adc.digital_out(digital_sig);

  sc_trace_file* tf = sc_create_vcd_trace_file("adc_wave"); //wavefor
  sc_trace(tf, clk, "clk");
  sc_trace(tf, analog_sig, "analog_in");
  sc_trace(tf, digital_sig, "digital_out");

  sc_start(2, SC_MS); // 2 ms 

  sc_close_vcd_trace_file(tf);
  std::cout << analog_sig.read()
          << "<A D>" << digital_sig.read() << std::endl;
  return 0;
}
