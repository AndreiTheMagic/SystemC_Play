# Jucat cu SystemC
## Andrei Musca
In acest repo am facut cateva module simple in SystemC:

- un calculator dintr-un modul

- un timer care are timpul pana la care inumara hardcoded

- un ADC care esantioneaza un semnal sinusoidal generat de alt modul

## calculator
  Foloseste 3 input: float a, float b, int op
            1 output: float result
  Un switch din modul face operatia data de op pentru a si b si o scoate pe result.
  Nu are clk

## timer 
  Folosete sc_time si evenimente pentru a afisa cand s-a scurs timpul
  Foloseste SC_THREAD si wait in loc de SC_METHOD

## ADC
  Modulul de conversie aplica o formula matematica la fiecare ciclu de clk (50 us)pe semnalul generat de generator la fiecare 1us
  Nu stiu daca asta insemna un ADC la inceput (work in progress)
Un waveform e pus in adc_wave.vcd

## build and run
    cmake -S . -B build
    cmake --build build

Facut pe Linux x64 cu c++ 17 (asa recomanda pe site)
Ma voi muta pe windows si VS2019/platform toolset 142 in viitor
