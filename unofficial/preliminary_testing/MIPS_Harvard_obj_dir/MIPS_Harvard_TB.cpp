// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See MIPS_Harvard_TB.h for the primary calling header

#include "MIPS_Harvard_TB.h"
#include "MIPS_Harvard_TB__Syms.h"

//==========

VL_CTOR_IMP(MIPS_Harvard_TB) {
    MIPS_Harvard_TB__Syms* __restrict vlSymsp = __VlSymsp = new MIPS_Harvard_TB__Syms(this, name());
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void MIPS_Harvard_TB::__Vconfigure(MIPS_Harvard_TB__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

MIPS_Harvard_TB::~MIPS_Harvard_TB() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void MIPS_Harvard_TB::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate MIPS_Harvard_TB::eval\n"); );
    MIPS_Harvard_TB__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../../src/mips_cpu.v", 5, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void MIPS_Harvard_TB::_eval_initial_loop(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../../src/mips_cpu.v", 5, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void MIPS_Harvard_TB::_initial__TOP__1(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_initial__TOP__1\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->data_read = 1U;
}

VL_INLINE_OPT void MIPS_Harvard_TB::_combo__TOP__2(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_combo__TOP__2\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mips_cpu__DOT__internal_clk = ((IData)(vlTOPp->clk) 
                                           & (IData)(vlTOPp->clk_enable));
}

void MIPS_Harvard_TB::_settle__TOP__3(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_settle__TOP__3\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mips_cpu__DOT__internal_clk = ((IData)(vlTOPp->clk) 
                                           & (IData)(vlTOPp->clk_enable));
    vlTOPp->data_writedata = vlTOPp->mips_cpu__DOT__write_data_memory;
    vlTOPp->data_write = vlTOPp->mips_cpu__DOT__memory_write_memory;
    vlTOPp->mips_cpu__DOT__result_writeback = ((IData)(vlTOPp->mips_cpu__DOT__memory_to_register_writeback)
                                                ? vlTOPp->mips_cpu__DOT__read_data_writeback
                                                : vlTOPp->mips_cpu__DOT__ALU_output_writeback);
    vlTOPp->data_address = vlTOPp->mips_cpu__DOT__ALU_output_memory;
    vlTOPp->instr_address = vlTOPp->mips_cpu__DOT__program_counter_fetch;
    vlTOPp->mips_cpu__DOT__sign_imm_decode = ((0xffff0000U 
                                               & (VL_NEGATE_I((IData)(
                                                                      (1U 
                                                                       & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                                          >> 0xfU)))) 
                                                  << 0x10U)) 
                                              | (0xffffU 
                                                 & vlTOPp->mips_cpu__DOT__instruction_decode));
    vlTOPp->mips_cpu__DOT__register_file_output_A_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__HI_LO_output)
            ? vlTOPp->mips_cpu__DOT__register_file__DOT__LO_reg
            : ((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                >> 0x15U))) ? vlTOPp->mips_cpu__DOT__register_file__DOT__registers
               [(0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                          >> 0x15U))] : 0U));
    vlTOPp->mips_cpu__DOT__register_file_output_B_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__HI_LO_output)
            ? vlTOPp->mips_cpu__DOT__register_file__DOT__HI_reg
            : ((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                >> 0x10U))) ? vlTOPp->mips_cpu__DOT__register_file__DOT__registers
               [(0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                          >> 0x10U))] : 0U));
    vlTOPp->mips_cpu__DOT__write_register_execute = 
        ((IData)(vlTOPp->mips_cpu__DOT__register_destination_execute)
          ? (IData)(vlTOPp->mips_cpu__DOT__Rd_execute)
          : (IData)(vlTOPp->mips_cpu__DOT__Rt_execute));
    vlTOPp->mips_cpu__DOT__forward_A_execute = ((((0U 
                                                   != (IData)(vlTOPp->mips_cpu__DOT__Rs_execute)) 
                                                  & ((IData)(vlTOPp->mips_cpu__DOT__Rs_execute) 
                                                     == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                                                 & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                                                 ? 2U
                                                 : 
                                                ((((0U 
                                                    != (IData)(vlTOPp->mips_cpu__DOT__Rs_execute)) 
                                                   & ((IData)(vlTOPp->mips_cpu__DOT__Rs_execute) 
                                                      == (IData)(vlTOPp->mips_cpu__DOT__write_register_writeback))) 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__register_write_writeback))
                                                  ? 1U
                                                  : 0U));
    vlTOPp->mips_cpu__DOT__forward_B_execute = ((((0U 
                                                   != (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
                                                  & ((IData)(vlTOPp->mips_cpu__DOT__Rt_execute) 
                                                     == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                                                 & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                                                 ? 2U
                                                 : 
                                                ((((0U 
                                                    != (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
                                                   & ((IData)(vlTOPp->mips_cpu__DOT__Rt_execute) 
                                                      == (IData)(vlTOPp->mips_cpu__DOT__write_register_writeback))) 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__register_write_writeback))
                                                  ? 1U
                                                  : 0U));
    vlTOPp->mips_cpu__DOT__control_unit__DOT__op = 
        (0x3fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                  >> 0x1aU));
    vlTOPp->mips_cpu__DOT__control_unit__DOT__funct 
        = (0x3fU & vlTOPp->mips_cpu__DOT__instruction_decode);
    if ((0x20U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
        } else {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                }
            } else {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                }
            }
        }
    } else {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
        } else {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x3fU;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    } else {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    }
                }
            } else {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    } else {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 1U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode 
                                = ((((0x18U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)) 
                                     | (0x19U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct))) 
                                    | (0x1aU == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct))) 
                                   | (0x1bU == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)));
                            vlTOPp->mips_cpu__DOT__ALU_function_decode 
                                = vlTOPp->mips_cpu__DOT__control_unit__DOT__funct;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode 
                                = ((8U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)) 
                                   | (9U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->mips_cpu__DOT__source_A_ALU_execute = (
                                                   (2U 
                                                    & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                     ? vlTOPp->mips_cpu__DOT__ALU_LO_output_writeback
                                                     : vlTOPp->mips_cpu__DOT__ALU_output_memory)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                     ? vlTOPp->mips_cpu__DOT__result_writeback
                                                     : vlTOPp->mips_cpu__DOT__register_file_output_A_execute));
    vlTOPp->mips_cpu__DOT__write_data_execute = ((2U 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                   ? vlTOPp->mips_cpu__DOT__ALU_HI_output_writeback
                                                   : vlTOPp->mips_cpu__DOT__ALU_output_memory)
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                   ? vlTOPp->mips_cpu__DOT__result_writeback
                                                   : vlTOPp->mips_cpu__DOT__register_file_output_B_execute));
    vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall 
        = ((((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                       >> 0x15U)) == (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
            | ((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                         >> 0x10U)) == (IData)(vlTOPp->mips_cpu__DOT__Rt_execute))) 
           & (IData)(vlTOPp->mips_cpu__DOT__memory_to_register_execute));
    vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall 
        = ((((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
             & (IData)(vlTOPp->mips_cpu__DOT__register_write_execute)) 
            & (((IData)(vlTOPp->mips_cpu__DOT__write_register_execute) 
                == (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                             >> 0x15U))) | ((IData)(vlTOPp->mips_cpu__DOT__write_register_execute) 
                                            == (0x1fU 
                                                & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                   >> 0x10U))))) 
           | (((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
               & (IData)(vlTOPp->mips_cpu__DOT__memory_to_register_memory)) 
              & (((IData)(vlTOPp->mips_cpu__DOT__write_register_memory) 
                  == (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                               >> 0x15U))) | ((IData)(vlTOPp->mips_cpu__DOT__write_register_memory) 
                                              == (0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x10U))))));
    vlTOPp->mips_cpu__DOT__stall_fetch = ((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
                                          | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall));
    vlTOPp->mips_cpu__DOT__stall_decode = ((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
                                           | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall));
    vlTOPp->mips_cpu__DOT__flush_execute_register = 
        (((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
          | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall)) 
         | (IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback));
    vlTOPp->mips_cpu__DOT__program_counter_source_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
           & (((((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                  >> 0x15U))) & ((0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x15U)) 
                                                 == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                ? vlTOPp->mips_cpu__DOT__ALU_output_memory
                : vlTOPp->mips_cpu__DOT__register_file_output_A_decode) 
              == ((((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                     >> 0x10U))) & 
                    ((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                               >> 0x10U)) == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                   & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                   ? vlTOPp->mips_cpu__DOT__ALU_output_memory
                   : vlTOPp->mips_cpu__DOT__register_file_output_B_decode)));
    vlTOPp->mips_cpu__DOT__source_B_ALU_execute = ((IData)(vlTOPp->mips_cpu__DOT__ALU_src_B_execute)
                                                    ? vlTOPp->mips_cpu__DOT__sign_imm_execute
                                                    : vlTOPp->mips_cpu__DOT__write_data_execute);
    vlTOPp->mips_cpu__DOT__flush_fetch_decode_register 
        = ((IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback) 
           | (IData)(vlTOPp->mips_cpu__DOT__program_counter_source_decode));
    vlTOPp->mips_cpu__DOT__program_counter_mux_1_out 
        = ((IData)(vlTOPp->mips_cpu__DOT__program_counter_source_decode)
            ? ((vlTOPp->mips_cpu__DOT__sign_imm_decode 
                << 2U) + vlTOPp->mips_cpu__DOT__program_counter_plus_four_decode)
            : ((IData)(4U) + vlTOPp->mips_cpu__DOT__program_counter_fetch));
    vlTOPp->mips_cpu__DOT__ALU_output_execute = 0U;
    if ((0x20U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
        vlTOPp->mips_cpu__DOT__ALU_output_execute = 
            ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
              ? ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                  ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? vlTOPp->mips_cpu__DOT__source_B_ALU_execute
                              : 0U) : 0U) : 0U) : 0U)
              : ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                  ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? 0U : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                               ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                   ? ((vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                       < vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                                       ? 1U : 0U) : 
                                  (VL_LTS_III(1,32,32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                                    ? 1U : 0U)) : 0U))
                  : ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (~ (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                    | vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 ^ ~ vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                          : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 | vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 & vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))
                      : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 - vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 - vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                          : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 + vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 + vlTOPp->mips_cpu__DOT__source_B_ALU_execute))))));
    } else {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                    vlTOPp->mips_cpu__DOT__ALU_output_execute = 0U;
                }
            } else {
                vlTOPp->mips_cpu__DOT__ALU_output_execute 
                    = ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? 0U : vlTOPp->mips_cpu__DOT__source_B_ALU_execute);
            }
        } else {
            vlTOPp->mips_cpu__DOT__ALU_output_execute 
                = ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                    ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? 0U : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                 ? 0U : vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                    : ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                            ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute))
                                : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute)))
                            : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? 0U : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                        << (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute))))
                        : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                            ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                >> 6U)))
                                : 0U) : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                          ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                             >> (0x1fU 
                                                 & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                    >> 6U)))
                                          : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                             << (0x1fU 
                                                 & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                    >> 6U)))))));
        }
    }
    vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output = VL_ULL(0);
    if ((1U & (~ ((IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute) 
                  >> 5U)))) {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                if ((1U & (~ ((IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute) 
                              >> 2U)))) {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = ((QData)((IData)(
                                                   VL_DIV_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))) 
                                   << 0x20U);
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                   + (QData)((IData)(
                                                     VL_MODDIV_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))));
                        } else {
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = ((QData)((IData)(
                                                   VL_DIVS_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))) 
                                   << 0x20U);
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                   + (QData)((IData)(
                                                     VL_MODDIVS_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))));
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                            = ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? ((QData)((IData)(vlTOPp->mips_cpu__DOT__source_A_ALU_execute)) 
                                   * (QData)((IData)(vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))
                                : VL_MULS_QQQ(64,64,64, 
                                              (((QData)((IData)(
                                                                VL_NEGATE_I((IData)(
                                                                                (1U 
                                                                                & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                                                >> 0x1fU)))))) 
                                                << 0x20U) 
                                               | (QData)((IData)(vlTOPp->mips_cpu__DOT__source_A_ALU_execute))), 
                                              (((QData)((IData)(
                                                                VL_NEGATE_I((IData)(
                                                                                (1U 
                                                                                & (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                                                                >> 0x1fU)))))) 
                                                << 0x20U) 
                                               | (QData)((IData)(vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))));
                    }
                }
            }
        }
    }
    vlTOPp->mips_cpu__DOT__ALU_HI_output_execute = (IData)(
                                                           (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                                            >> 0x20U));
    vlTOPp->mips_cpu__DOT__ALU_LO_output_execute = (IData)(vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output);
}

VL_INLINE_OPT void MIPS_Harvard_TB::_sequent__TOP__4(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_sequent__TOP__4\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mips_cpu__DOT__write_data_memory = vlTOPp->mips_cpu__DOT__write_data_execute;
    vlTOPp->mips_cpu__DOT__ALU_LO_output_writeback 
        = vlTOPp->mips_cpu__DOT__ALU_LO_output_memory;
    vlTOPp->mips_cpu__DOT__sign_imm_execute = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
                                                ? 0U
                                                : vlTOPp->mips_cpu__DOT__sign_imm_decode);
    vlTOPp->mips_cpu__DOT__hi_lo_register_write_writeback 
        = vlTOPp->mips_cpu__DOT__hi_lo_register_write_memory;
    vlTOPp->mips_cpu__DOT__memory_write_memory = vlTOPp->mips_cpu__DOT__memory_write_execute;
    vlTOPp->mips_cpu__DOT__ALU_function_execute = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
                                                    ? 0U
                                                    : (IData)(vlTOPp->mips_cpu__DOT__ALU_function_decode));
    vlTOPp->mips_cpu__DOT__register_file_output_A_execute 
        = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
            ? 0U : vlTOPp->mips_cpu__DOT__register_file_output_A_decode);
    vlTOPp->mips_cpu__DOT__ALU_HI_output_writeback 
        = vlTOPp->mips_cpu__DOT__ALU_HI_output_memory;
    vlTOPp->mips_cpu__DOT__ALU_src_B_execute = ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
                                                & (IData)(vlTOPp->mips_cpu__DOT__ALU_src_B_decode));
    vlTOPp->mips_cpu__DOT__register_destination_execute 
        = ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
           & (IData)(vlTOPp->mips_cpu__DOT__register_destination_decode));
    vlTOPp->mips_cpu__DOT__register_file_output_B_execute 
        = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
            ? 0U : vlTOPp->mips_cpu__DOT__register_file_output_B_decode);
    if ((1U & (~ (IData)(vlTOPp->mips_cpu__DOT__stall_decode)))) {
        vlTOPp->mips_cpu__DOT__program_counter_plus_four_decode 
            = ((IData)(vlTOPp->mips_cpu__DOT__flush_fetch_decode_register)
                ? 0U : ((IData)(4U) + vlTOPp->mips_cpu__DOT__program_counter_fetch));
    }
    vlTOPp->mips_cpu__DOT__read_data_writeback = vlTOPp->data_readdata;
    vlTOPp->mips_cpu__DOT__memory_to_register_writeback 
        = vlTOPp->mips_cpu__DOT__memory_to_register_memory;
    vlTOPp->mips_cpu__DOT__ALU_output_writeback = vlTOPp->mips_cpu__DOT__ALU_output_memory;
    vlTOPp->mips_cpu__DOT__Rd_execute = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
                                          ? 0U : (0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0xbU)));
    vlTOPp->mips_cpu__DOT__Rs_execute = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
                                          ? 0U : (0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x15U)));
    vlTOPp->mips_cpu__DOT__write_register_writeback 
        = vlTOPp->mips_cpu__DOT__write_register_memory;
    vlTOPp->mips_cpu__DOT__Rt_execute = ((IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)
                                          ? 0U : (0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x10U)));
    vlTOPp->mips_cpu__DOT__register_write_writeback 
        = vlTOPp->mips_cpu__DOT__register_write_memory;
    vlTOPp->data_writedata = vlTOPp->mips_cpu__DOT__write_data_memory;
    vlTOPp->mips_cpu__DOT__ALU_LO_output_memory = vlTOPp->mips_cpu__DOT__ALU_LO_output_execute;
    vlTOPp->mips_cpu__DOT__hi_lo_register_write_memory 
        = vlTOPp->mips_cpu__DOT__hi_lo_register_write_execute;
    vlTOPp->data_write = vlTOPp->mips_cpu__DOT__memory_write_memory;
    vlTOPp->mips_cpu__DOT__memory_write_execute = (
                                                   (~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
                                                   & (IData)(vlTOPp->mips_cpu__DOT__memory_write_decode));
    vlTOPp->mips_cpu__DOT__ALU_HI_output_memory = vlTOPp->mips_cpu__DOT__ALU_HI_output_execute;
    if ((1U & (~ (IData)(vlTOPp->mips_cpu__DOT__stall_fetch)))) {
        vlTOPp->mips_cpu__DOT__program_counter_fetch 
            = ((IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback)
                ? vlTOPp->mips_cpu__DOT__result_writeback
                : vlTOPp->mips_cpu__DOT__program_counter_mux_1_out);
    }
    vlTOPp->mips_cpu__DOT__memory_to_register_memory 
        = vlTOPp->mips_cpu__DOT__memory_to_register_execute;
    vlTOPp->mips_cpu__DOT__ALU_output_memory = vlTOPp->mips_cpu__DOT__ALU_output_execute;
    vlTOPp->mips_cpu__DOT__write_register_memory = vlTOPp->mips_cpu__DOT__write_register_execute;
    if ((1U & (~ (IData)(vlTOPp->mips_cpu__DOT__stall_decode)))) {
        vlTOPp->mips_cpu__DOT__instruction_decode = 
            ((IData)(vlTOPp->mips_cpu__DOT__flush_fetch_decode_register)
              ? 0U : vlTOPp->instr_readdata);
    }
    vlTOPp->mips_cpu__DOT__register_write_memory = vlTOPp->mips_cpu__DOT__register_write_execute;
    vlTOPp->mips_cpu__DOT__result_writeback = ((IData)(vlTOPp->mips_cpu__DOT__memory_to_register_writeback)
                                                ? vlTOPp->mips_cpu__DOT__read_data_writeback
                                                : vlTOPp->mips_cpu__DOT__ALU_output_writeback);
    vlTOPp->mips_cpu__DOT__write_register_execute = 
        ((IData)(vlTOPp->mips_cpu__DOT__register_destination_execute)
          ? (IData)(vlTOPp->mips_cpu__DOT__Rd_execute)
          : (IData)(vlTOPp->mips_cpu__DOT__Rt_execute));
    vlTOPp->mips_cpu__DOT__hi_lo_register_write_execute 
        = ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
           & (IData)(vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode));
    vlTOPp->instr_address = vlTOPp->mips_cpu__DOT__program_counter_fetch;
    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback 
        = vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_memory;
    vlTOPp->mips_cpu__DOT__memory_to_register_execute 
        = ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
           & (IData)(vlTOPp->mips_cpu__DOT__memory_to_register_decode));
    vlTOPp->data_address = vlTOPp->mips_cpu__DOT__ALU_output_memory;
    vlTOPp->mips_cpu__DOT__sign_imm_decode = ((0xffff0000U 
                                               & (VL_NEGATE_I((IData)(
                                                                      (1U 
                                                                       & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                                          >> 0xfU)))) 
                                                  << 0x10U)) 
                                              | (0xffffU 
                                                 & vlTOPp->mips_cpu__DOT__instruction_decode));
    vlTOPp->mips_cpu__DOT__register_write_execute = 
        ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
         & (IData)(vlTOPp->mips_cpu__DOT__register_write_decode));
    vlTOPp->mips_cpu__DOT__forward_A_execute = ((((0U 
                                                   != (IData)(vlTOPp->mips_cpu__DOT__Rs_execute)) 
                                                  & ((IData)(vlTOPp->mips_cpu__DOT__Rs_execute) 
                                                     == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                                                 & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                                                 ? 2U
                                                 : 
                                                ((((0U 
                                                    != (IData)(vlTOPp->mips_cpu__DOT__Rs_execute)) 
                                                   & ((IData)(vlTOPp->mips_cpu__DOT__Rs_execute) 
                                                      == (IData)(vlTOPp->mips_cpu__DOT__write_register_writeback))) 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__register_write_writeback))
                                                  ? 1U
                                                  : 0U));
    vlTOPp->mips_cpu__DOT__forward_B_execute = ((((0U 
                                                   != (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
                                                  & ((IData)(vlTOPp->mips_cpu__DOT__Rt_execute) 
                                                     == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                                                 & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                                                 ? 2U
                                                 : 
                                                ((((0U 
                                                    != (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
                                                   & ((IData)(vlTOPp->mips_cpu__DOT__Rt_execute) 
                                                      == (IData)(vlTOPp->mips_cpu__DOT__write_register_writeback))) 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__register_write_writeback))
                                                  ? 1U
                                                  : 0U));
    vlTOPp->mips_cpu__DOT__source_A_ALU_execute = (
                                                   (2U 
                                                    & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                     ? vlTOPp->mips_cpu__DOT__ALU_LO_output_writeback
                                                     : vlTOPp->mips_cpu__DOT__ALU_output_memory)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlTOPp->mips_cpu__DOT__forward_A_execute))
                                                     ? vlTOPp->mips_cpu__DOT__result_writeback
                                                     : vlTOPp->mips_cpu__DOT__register_file_output_A_execute));
    vlTOPp->mips_cpu__DOT__write_data_execute = ((2U 
                                                  & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                   ? vlTOPp->mips_cpu__DOT__ALU_HI_output_writeback
                                                   : vlTOPp->mips_cpu__DOT__ALU_output_memory)
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->mips_cpu__DOT__forward_B_execute))
                                                   ? vlTOPp->mips_cpu__DOT__result_writeback
                                                   : vlTOPp->mips_cpu__DOT__register_file_output_B_execute));
    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_memory 
        = vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_execute;
    vlTOPp->mips_cpu__DOT__source_B_ALU_execute = ((IData)(vlTOPp->mips_cpu__DOT__ALU_src_B_execute)
                                                    ? vlTOPp->mips_cpu__DOT__sign_imm_execute
                                                    : vlTOPp->mips_cpu__DOT__write_data_execute);
    vlTOPp->mips_cpu__DOT__ALU_output_execute = 0U;
    if ((0x20U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
        vlTOPp->mips_cpu__DOT__ALU_output_execute = 
            ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
              ? ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                  ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? vlTOPp->mips_cpu__DOT__source_B_ALU_execute
                              : 0U) : 0U) : 0U) : 0U)
              : ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                  ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? 0U : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                               ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                   ? ((vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                       < vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                                       ? 1U : 0U) : 
                                  (VL_LTS_III(1,32,32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                                    ? 1U : 0U)) : 0U))
                  : ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                      ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (~ (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                    | vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 ^ ~ vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                          : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 | vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 & vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))
                      : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                          ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 - vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 - vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                          : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                              ? (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 + vlTOPp->mips_cpu__DOT__source_B_ALU_execute)
                              : (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                 + vlTOPp->mips_cpu__DOT__source_B_ALU_execute))))));
    } else {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                    vlTOPp->mips_cpu__DOT__ALU_output_execute = 0U;
                }
            } else {
                vlTOPp->mips_cpu__DOT__ALU_output_execute 
                    = ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? 0U : vlTOPp->mips_cpu__DOT__source_B_ALU_execute);
            }
        } else {
            vlTOPp->mips_cpu__DOT__ALU_output_execute 
                = ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                    ? ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? 0U : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                 ? 0U : vlTOPp->mips_cpu__DOT__source_B_ALU_execute))
                    : ((4U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                        ? ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                            ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute))
                                : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute)))
                            : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? 0U : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                        << (0x1fU & vlTOPp->mips_cpu__DOT__source_A_ALU_execute))))
                        : ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                            ? ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                   >> (0x1fU & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                >> 6U)))
                                : 0U) : ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                          ? (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                             >> (0x1fU 
                                                 & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                    >> 6U)))
                                          : (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                             << (0x1fU 
                                                 & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                    >> 6U)))))));
        }
    }
    vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output = VL_ULL(0);
    if ((1U & (~ ((IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute) 
                  >> 5U)))) {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                if ((1U & (~ ((IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute) 
                              >> 2U)))) {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))) {
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = ((QData)((IData)(
                                                   VL_DIV_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))) 
                                   << 0x20U);
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                   + (QData)((IData)(
                                                     VL_MODDIV_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))));
                        } else {
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = ((QData)((IData)(
                                                   VL_DIVS_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))) 
                                   << 0x20U);
                            vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                = (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                   + (QData)((IData)(
                                                     VL_MODDIVS_III(32, vlTOPp->mips_cpu__DOT__source_A_ALU_execute, vlTOPp->mips_cpu__DOT__source_B_ALU_execute))));
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                            = ((1U & (IData)(vlTOPp->mips_cpu__DOT__ALU_function_execute))
                                ? ((QData)((IData)(vlTOPp->mips_cpu__DOT__source_A_ALU_execute)) 
                                   * (QData)((IData)(vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))
                                : VL_MULS_QQQ(64,64,64, 
                                              (((QData)((IData)(
                                                                VL_NEGATE_I((IData)(
                                                                                (1U 
                                                                                & (vlTOPp->mips_cpu__DOT__source_A_ALU_execute 
                                                                                >> 0x1fU)))))) 
                                                << 0x20U) 
                                               | (QData)((IData)(vlTOPp->mips_cpu__DOT__source_A_ALU_execute))), 
                                              (((QData)((IData)(
                                                                VL_NEGATE_I((IData)(
                                                                                (1U 
                                                                                & (vlTOPp->mips_cpu__DOT__source_B_ALU_execute 
                                                                                >> 0x1fU)))))) 
                                                << 0x20U) 
                                               | (QData)((IData)(vlTOPp->mips_cpu__DOT__source_B_ALU_execute)))));
                    }
                }
            }
        }
    }
    vlTOPp->mips_cpu__DOT__ALU_HI_output_execute = (IData)(
                                                           (vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output 
                                                            >> 0x20U));
    vlTOPp->mips_cpu__DOT__ALU_LO_output_execute = (IData)(vlTOPp->mips_cpu__DOT__alu__DOT__ALU_HI_LO_output);
    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_execute 
        = ((~ (IData)(vlTOPp->mips_cpu__DOT__flush_execute_register)) 
           & (IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode));
    vlTOPp->mips_cpu__DOT__control_unit__DOT__op = 
        (0x3fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                  >> 0x1aU));
    vlTOPp->mips_cpu__DOT__control_unit__DOT__funct 
        = (0x3fU & vlTOPp->mips_cpu__DOT__instruction_decode);
    if ((0x20U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
        } else {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                }
            } else {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                }
            }
        }
    } else {
        if ((0x10U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
        } else {
            if ((8U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x3fU;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    } else {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    }
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    } else {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 1U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0x21U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        }
                    }
                }
            } else {
                if ((4U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                    vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                    vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                    vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                    vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                    vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                    vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                    vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                } else {
                    if ((2U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                        vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                        vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                        vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                        vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                        vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                        vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                        vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                    } else {
                        if ((1U & (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__op))) {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 0U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_function_decode = 0U;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode = 0U;
                        } else {
                            vlTOPp->mips_cpu__DOT__register_write_decode = 1U;
                            vlTOPp->mips_cpu__DOT__memory_to_register_decode = 0U;
                            vlTOPp->mips_cpu__DOT__memory_write_decode = 0U;
                            vlTOPp->mips_cpu__DOT__ALU_src_B_decode = 0U;
                            vlTOPp->mips_cpu__DOT__register_destination_decode = 1U;
                            vlTOPp->mips_cpu__DOT__branch_decode = 0U;
                            vlTOPp->mips_cpu__DOT__hi_lo_register_write_decode 
                                = ((((0x18U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)) 
                                     | (0x19U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct))) 
                                    | (0x1aU == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct))) 
                                   | (0x1bU == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)));
                            vlTOPp->mips_cpu__DOT__ALU_function_decode 
                                = vlTOPp->mips_cpu__DOT__control_unit__DOT__funct;
                            vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_decode 
                                = ((8U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)) 
                                   | (9U == (IData)(vlTOPp->mips_cpu__DOT__control_unit__DOT__funct)));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall 
        = ((((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                       >> 0x15U)) == (IData)(vlTOPp->mips_cpu__DOT__Rt_execute)) 
            | ((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                         >> 0x10U)) == (IData)(vlTOPp->mips_cpu__DOT__Rt_execute))) 
           & (IData)(vlTOPp->mips_cpu__DOT__memory_to_register_execute));
    vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall 
        = ((((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
             & (IData)(vlTOPp->mips_cpu__DOT__register_write_execute)) 
            & (((IData)(vlTOPp->mips_cpu__DOT__write_register_execute) 
                == (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                             >> 0x15U))) | ((IData)(vlTOPp->mips_cpu__DOT__write_register_execute) 
                                            == (0x1fU 
                                                & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                   >> 0x10U))))) 
           | (((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
               & (IData)(vlTOPp->mips_cpu__DOT__memory_to_register_memory)) 
              & (((IData)(vlTOPp->mips_cpu__DOT__write_register_memory) 
                  == (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                               >> 0x15U))) | ((IData)(vlTOPp->mips_cpu__DOT__write_register_memory) 
                                              == (0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x10U))))));
    vlTOPp->mips_cpu__DOT__stall_fetch = ((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
                                          | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall));
    vlTOPp->mips_cpu__DOT__stall_decode = ((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
                                           | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall));
    vlTOPp->mips_cpu__DOT__flush_execute_register = 
        (((IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__branchstall) 
          | (IData)(vlTOPp->mips_cpu__DOT__hazard_unit__DOT__lwstall)) 
         | (IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback));
}

VL_INLINE_OPT void MIPS_Harvard_TB::_sequent__TOP__5(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_sequent__TOP__5\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*4:0*/ __Vdlyvdim0__mips_cpu__DOT__register_file__DOT__registers__v0;
    CData/*0:0*/ __Vdlyvset__mips_cpu__DOT__register_file__DOT__registers__v0;
    IData/*31:0*/ __Vdlyvval__mips_cpu__DOT__register_file__DOT__registers__v0;
    // Body
    __Vdlyvset__mips_cpu__DOT__register_file__DOT__registers__v0 = 0U;
    if (vlTOPp->mips_cpu__DOT__hi_lo_register_write_writeback) {
        vlTOPp->mips_cpu__DOT__register_file__DOT__LO_reg 
            = vlTOPp->mips_cpu__DOT__ALU_LO_output_writeback;
    }
    if (vlTOPp->mips_cpu__DOT__hi_lo_register_write_writeback) {
        vlTOPp->mips_cpu__DOT__register_file__DOT__HI_reg 
            = vlTOPp->mips_cpu__DOT__ALU_HI_output_writeback;
    }
    if (vlTOPp->mips_cpu__DOT__register_write_writeback) {
        __Vdlyvval__mips_cpu__DOT__register_file__DOT__registers__v0 
            = vlTOPp->mips_cpu__DOT__result_writeback;
        __Vdlyvset__mips_cpu__DOT__register_file__DOT__registers__v0 = 1U;
        __Vdlyvdim0__mips_cpu__DOT__register_file__DOT__registers__v0 
            = vlTOPp->mips_cpu__DOT__write_register_writeback;
    }
    if (__Vdlyvset__mips_cpu__DOT__register_file__DOT__registers__v0) {
        vlTOPp->mips_cpu__DOT__register_file__DOT__registers[__Vdlyvdim0__mips_cpu__DOT__register_file__DOT__registers__v0] 
            = __Vdlyvval__mips_cpu__DOT__register_file__DOT__registers__v0;
    }
}

VL_INLINE_OPT void MIPS_Harvard_TB::_multiclk__TOP__6(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_multiclk__TOP__6\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mips_cpu__DOT__register_file_output_A_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__HI_LO_output)
            ? vlTOPp->mips_cpu__DOT__register_file__DOT__LO_reg
            : ((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                >> 0x15U))) ? vlTOPp->mips_cpu__DOT__register_file__DOT__registers
               [(0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                          >> 0x15U))] : 0U));
    vlTOPp->mips_cpu__DOT__register_file_output_B_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__HI_LO_output)
            ? vlTOPp->mips_cpu__DOT__register_file__DOT__HI_reg
            : ((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                >> 0x10U))) ? vlTOPp->mips_cpu__DOT__register_file__DOT__registers
               [(0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                          >> 0x10U))] : 0U));
    vlTOPp->mips_cpu__DOT__program_counter_source_decode 
        = ((IData)(vlTOPp->mips_cpu__DOT__branch_decode) 
           & (((((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                  >> 0x15U))) & ((0x1fU 
                                                  & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                                     >> 0x15U)) 
                                                 == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                ? vlTOPp->mips_cpu__DOT__ALU_output_memory
                : vlTOPp->mips_cpu__DOT__register_file_output_A_decode) 
              == ((((0U != (0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                                     >> 0x10U))) & 
                    ((0x1fU & (vlTOPp->mips_cpu__DOT__instruction_decode 
                               >> 0x10U)) == (IData)(vlTOPp->mips_cpu__DOT__write_register_memory))) 
                   & (IData)(vlTOPp->mips_cpu__DOT__register_write_memory))
                   ? vlTOPp->mips_cpu__DOT__ALU_output_memory
                   : vlTOPp->mips_cpu__DOT__register_file_output_B_decode)));
    vlTOPp->mips_cpu__DOT__flush_fetch_decode_register 
        = ((IData)(vlTOPp->mips_cpu__DOT__program_counter_multiplexer_jump_writeback) 
           | (IData)(vlTOPp->mips_cpu__DOT__program_counter_source_decode));
    vlTOPp->mips_cpu__DOT__program_counter_mux_1_out 
        = ((IData)(vlTOPp->mips_cpu__DOT__program_counter_source_decode)
            ? ((vlTOPp->mips_cpu__DOT__sign_imm_decode 
                << 2U) + vlTOPp->mips_cpu__DOT__program_counter_plus_four_decode)
            : ((IData)(4U) + vlTOPp->mips_cpu__DOT__program_counter_fetch));
}

void MIPS_Harvard_TB::_eval(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_eval\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    if (((IData)(vlTOPp->mips_cpu__DOT__internal_clk) 
         & (~ (IData)(vlTOPp->__Vclklast__TOP__mips_cpu__DOT__internal_clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
        vlTOPp->__Vm_traceActivity = (4U | vlTOPp->__Vm_traceActivity);
    }
    if (((~ (IData)(vlTOPp->mips_cpu__DOT__internal_clk)) 
         & (IData)(vlTOPp->__Vclklast__TOP__mips_cpu__DOT__internal_clk))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
        vlTOPp->__Vm_traceActivity = (8U | vlTOPp->__Vm_traceActivity);
    }
    if (((IData)(vlTOPp->mips_cpu__DOT__internal_clk) 
         ^ (IData)(vlTOPp->__Vclklast__TOP__mips_cpu__DOT__internal_clk))) {
        vlTOPp->_multiclk__TOP__6(vlSymsp);
        vlTOPp->__Vm_traceActivity = (0x10U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__mips_cpu__DOT__internal_clk 
        = vlTOPp->mips_cpu__DOT__internal_clk;
}

void MIPS_Harvard_TB::_eval_initial(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_eval_initial\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__mips_cpu__DOT__internal_clk 
        = vlTOPp->mips_cpu__DOT__internal_clk;
}

void MIPS_Harvard_TB::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::final\n"); );
    // Variables
    MIPS_Harvard_TB__Syms* __restrict vlSymsp = this->__VlSymsp;
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void MIPS_Harvard_TB::_eval_settle(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_eval_settle\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
}

VL_INLINE_OPT QData MIPS_Harvard_TB::_change_request(MIPS_Harvard_TB__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_change_request\n"); );
    MIPS_Harvard_TB* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void MIPS_Harvard_TB::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((clk_enable & 0xfeU))) {
        Verilated::overWidthError("clk_enable");}
}
#endif  // VL_DEBUG

void MIPS_Harvard_TB::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    MIPS_Harvard_TB::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    active = VL_RAND_RESET_I(1);
    register_v0 = VL_RAND_RESET_I(32);
    clk_enable = VL_RAND_RESET_I(1);
    instr_address = VL_RAND_RESET_I(32);
    instr_readdata = VL_RAND_RESET_I(32);
    data_address = VL_RAND_RESET_I(32);
    data_write = VL_RAND_RESET_I(1);
    data_read = VL_RAND_RESET_I(1);
    data_writedata = VL_RAND_RESET_I(32);
    data_readdata = VL_RAND_RESET_I(32);
    mips_cpu__DOT__internal_clk = VL_RAND_RESET_I(1);
    mips_cpu__DOT__HI_LO_output = VL_RAND_RESET_I(1);
    mips_cpu__DOT__program_counter_fetch = VL_RAND_RESET_I(32);
    mips_cpu__DOT__program_counter_mux_1_out = VL_RAND_RESET_I(32);
    mips_cpu__DOT__program_counter_source_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__register_write_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_to_register_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_write_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__ALU_src_B_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__register_destination_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__branch_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__hi_lo_register_write_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__ALU_function_decode = VL_RAND_RESET_I(6);
    mips_cpu__DOT__program_counter_multiplexer_jump_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__flush_decode_execute_register = VL_RAND_RESET_I(1);
    mips_cpu__DOT__instruction_decode = VL_RAND_RESET_I(32);
    mips_cpu__DOT__program_counter_plus_four_decode = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_file_output_A_decode = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_file_output_B_decode = VL_RAND_RESET_I(32);
    mips_cpu__DOT__sign_imm_decode = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_destination_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_to_register_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_write_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__write_register_execute = VL_RAND_RESET_I(5);
    mips_cpu__DOT__ALU_src_B_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__ALU_function_execute = VL_RAND_RESET_I(6);
    mips_cpu__DOT__hi_lo_register_write_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__register_write_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__program_counter_multiplexer_jump_execute = VL_RAND_RESET_I(1);
    mips_cpu__DOT__register_file_output_A_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_file_output_B_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__source_A_ALU_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__source_B_ALU_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__write_data_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_output_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_HI_output_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_LO_output_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__Rs_execute = VL_RAND_RESET_I(5);
    mips_cpu__DOT__Rt_execute = VL_RAND_RESET_I(5);
    mips_cpu__DOT__Rd_execute = VL_RAND_RESET_I(5);
    mips_cpu__DOT__sign_imm_execute = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_write_memory = VL_RAND_RESET_I(1);
    mips_cpu__DOT__write_register_memory = VL_RAND_RESET_I(5);
    mips_cpu__DOT__memory_to_register_memory = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_write_memory = VL_RAND_RESET_I(1);
    mips_cpu__DOT__hi_lo_register_write_memory = VL_RAND_RESET_I(1);
    mips_cpu__DOT__program_counter_multiplexer_jump_memory = VL_RAND_RESET_I(1);
    mips_cpu__DOT__ALU_output_memory = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_HI_output_memory = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_LO_output_memory = VL_RAND_RESET_I(32);
    mips_cpu__DOT__write_data_memory = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_write_writeback = VL_RAND_RESET_I(1);
    mips_cpu__DOT__hi_lo_register_write_writeback = VL_RAND_RESET_I(1);
    mips_cpu__DOT__memory_to_register_writeback = VL_RAND_RESET_I(1);
    mips_cpu__DOT__program_counter_multiplexer_jump_writeback = VL_RAND_RESET_I(1);
    mips_cpu__DOT__write_register_writeback = VL_RAND_RESET_I(5);
    mips_cpu__DOT__result_writeback = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_HI_output_writeback = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_LO_output_writeback = VL_RAND_RESET_I(32);
    mips_cpu__DOT__ALU_output_writeback = VL_RAND_RESET_I(32);
    mips_cpu__DOT__read_data_writeback = VL_RAND_RESET_I(32);
    mips_cpu__DOT__stall_fetch = VL_RAND_RESET_I(1);
    mips_cpu__DOT__stall_decode = VL_RAND_RESET_I(1);
    mips_cpu__DOT__flush_execute_register = VL_RAND_RESET_I(1);
    mips_cpu__DOT__forward_A_execute = VL_RAND_RESET_I(2);
    mips_cpu__DOT__forward_B_execute = VL_RAND_RESET_I(2);
    mips_cpu__DOT__flush_fetch_decode_register = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            mips_cpu__DOT__register_file__DOT__registers[__Vi0] = VL_RAND_RESET_I(32);
    }}
    mips_cpu__DOT__register_file__DOT__HI_reg = VL_RAND_RESET_I(32);
    mips_cpu__DOT__register_file__DOT__LO_reg = VL_RAND_RESET_I(32);
    mips_cpu__DOT__control_unit__DOT__op = VL_RAND_RESET_I(6);
    mips_cpu__DOT__control_unit__DOT__funct = VL_RAND_RESET_I(6);
    mips_cpu__DOT__alu__DOT__ALU_HI_LO_output = VL_RAND_RESET_Q(64);
    mips_cpu__DOT__hazard_unit__DOT__lwstall = VL_RAND_RESET_I(1);
    mips_cpu__DOT__hazard_unit__DOT__branchstall = VL_RAND_RESET_I(1);
    __Vm_traceActivity = 0;
}