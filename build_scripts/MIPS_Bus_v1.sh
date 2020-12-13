#!/bin/bash
set -e
cd "$(dirname "$0")"
cd ../rtl

top_level=("../../rtl/mips_cpu_bus.v")
lower_level=(
    "../../rtl/Adder.v"
    "../../rtl/ALU.v"
    "../../rtl/Control_Unit.v"
    "../../rtl/Comparator.v"
    "../../rtl/Hazard_Unit.v"
    "../../rtl/MUX_2INPUT.v"
    "../../rtl/MUX_4INPUT.v"
    "../../rtl/Program_Counter.v"
    "../../rtl/Register_File.v"
    "../../rtl/pipeline_registers_bus/Decode_Execute_Register.v"
    "../../rtl/pipeline_registers_bus/Execute_Memory_Register.v"
    "../../rtl/pipeline_registers_bus/Fetch_Decode_Register.v"
    "../../rtl/pipeline_registers_bus/Memory_Writeback_Register.v"
    "../../rtl/ALU_Input_Mux.v"
)
while getopts gcl flag
do
    case "${flag}" in
        g) cd ../unofficial/preliminary_testing;
            verilator -Wall --trace +1800-2012ext+.v --debug -cc  $top_level ${lower_level[@]} --prefix MIPS_Bus_TB --Mdir MIPS_Bus_obj_dir;
            echo "generating c++ code"
            
            exit 0 ;;
        c)  cd ../unofficial/preliminary_testing;
            verilator -Wall --trace +1800-2012ext+.v --debug -cc  $top_level ${lower_level[@]} --prefix MIPS_Bus_TB --Mdir MIPS_Bus_obj_dir --exe mips_v0.cpp -CFLAGS "-std=c++17 -g";
            echo "compiling"
            
            cd MIPS_Bus_obj_dir;
            make -j4 -f MIPS_Bus_TB.mk MIPS_Bus_TB;
            
            ./MIPS_Bus_TB;
            gtkwave trace.vcd;
            exit 0 ;;
        l) cd ../unofficial/preliminary_testing;
            echo "linting";
            verilator -Wall --trace +1800-2012ext+.v $top_level ${lower_level[@]} --lint-only;
            
            exit 0 ;;
    esac
done
echo "No flag passed options are:"
echo "  (-g to generate c++ headers from verilog)"
echo "  (-l for lint)"
echo "  (-c for compile and run)"
exit 1