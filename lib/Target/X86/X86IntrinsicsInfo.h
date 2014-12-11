//===-- X86IntinsicsInfo.h - X86 Instrinsics ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the details for lowering X86 intrinsics
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_X86_X86INTRINSICSINFO_H
#define LLVM_LIB_TARGET_X86_X86INTRINSICSINFO_H

namespace llvm {

enum IntrinsicType {
  INTR_NO_TYPE,
  GATHER, SCATTER, PREFETCH, RDSEED, RDRAND, RDPMC, RDTSC, XTEST, ADX,
  INTR_TYPE_1OP, INTR_TYPE_2OP, INTR_TYPE_3OP,
  CMP_MASK, CMP_MASK_CC, VSHIFT, VSHIFT_MASK, COMI,
  INTR_TYPE_1OP_MASK_RM, INTR_TYPE_2OP_MASK, INTR_TYPE_SCALAR_MASK_RM,
  COMPRESS_TO_REG, COMPRESS_TO_MEM
};

struct IntrinsicData {

  unsigned      Id;
  IntrinsicType Type;
  unsigned      Opc0;
  unsigned      Opc1;

  bool operator<(const IntrinsicData &RHS) const {
    return Id < RHS.Id;
  }
  bool operator==(const IntrinsicData &RHS) const {
    return RHS.Id == Id;
  }
};

#define X86_INTRINSIC_DATA(id, type, op0, op1) \
  { Intrinsic::x86_##id, type, op0, op1 }

/*
 * IntrinsicsWithChain - the table should be sorted by Intrinsic ID - in
 * the alphabetical order.
 */
static const IntrinsicData IntrinsicsWithChain[] = {
  X86_INTRINSIC_DATA(addcarry_u32,  ADX, X86ISD::ADC, 0),
  X86_INTRINSIC_DATA(addcarry_u64,  ADX, X86ISD::ADC, 0),
  X86_INTRINSIC_DATA(addcarryx_u32, ADX, X86ISD::ADC, 0),
  X86_INTRINSIC_DATA(addcarryx_u64, ADX, X86ISD::ADC, 0),

  X86_INTRINSIC_DATA(avx512_gather_dpd_512, GATHER, X86::VGATHERDPDZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_dpi_512, GATHER, X86::VPGATHERDDZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_dpq_512, GATHER, X86::VPGATHERDQZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_dps_512, GATHER, X86::VGATHERDPSZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_qpd_512, GATHER, X86::VGATHERQPDZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_qpi_512, GATHER, X86::VPGATHERQDZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_qpq_512, GATHER, X86::VPGATHERQQZrm, 0),
  X86_INTRINSIC_DATA(avx512_gather_qps_512, GATHER, X86::VGATHERQPSZrm, 0),

  X86_INTRINSIC_DATA(avx512_gatherpf_dpd_512, PREFETCH,
                     X86::VGATHERPF0DPDm, X86::VGATHERPF1DPDm),
  X86_INTRINSIC_DATA(avx512_gatherpf_dps_512, PREFETCH,
                     X86::VGATHERPF0DPSm, X86::VGATHERPF1DPSm),
  X86_INTRINSIC_DATA(avx512_gatherpf_qpd_512, PREFETCH,
                     X86::VGATHERPF0QPDm, X86::VGATHERPF1QPDm),
  X86_INTRINSIC_DATA(avx512_gatherpf_qps_512, PREFETCH,
                     X86::VGATHERPF0QPSm, X86::VGATHERPF1QPSm),

  X86_INTRINSIC_DATA(avx512_mask_compress_store_d_128,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_d_256,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_d_512,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_pd_128,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_pd_256,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_pd_512,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_ps_128,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_ps_256,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_ps_512,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_q_128,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_q_256,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_store_q_512,
                     COMPRESS_TO_MEM, X86ISD::COMPRESS, 0),

  X86_INTRINSIC_DATA(avx512_scatter_dpd_512, SCATTER, X86::VSCATTERDPDZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_dpi_512, SCATTER, X86::VPSCATTERDDZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_dpq_512, SCATTER, X86::VPSCATTERDQZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_dps_512, SCATTER, X86::VSCATTERDPSZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_qpd_512, SCATTER, X86::VSCATTERQPDZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_qpi_512, SCATTER, X86::VPSCATTERQDZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_qpq_512, SCATTER, X86::VPSCATTERQQZmr, 0),
  X86_INTRINSIC_DATA(avx512_scatter_qps_512, SCATTER, X86::VSCATTERQPSZmr, 0),

  X86_INTRINSIC_DATA(avx512_scatterpf_dpd_512, PREFETCH,
                     X86::VSCATTERPF0DPDm, X86::VSCATTERPF1DPDm),
  X86_INTRINSIC_DATA(avx512_scatterpf_dps_512, PREFETCH,
                     X86::VSCATTERPF0DPSm, X86::VSCATTERPF1DPSm),
  X86_INTRINSIC_DATA(avx512_scatterpf_qpd_512, PREFETCH,
                     X86::VSCATTERPF0QPDm, X86::VSCATTERPF1QPDm),
  X86_INTRINSIC_DATA(avx512_scatterpf_qps_512, PREFETCH,
                     X86::VSCATTERPF0QPSm, X86::VSCATTERPF1QPSm),

  X86_INTRINSIC_DATA(rdpmc,     RDPMC,  X86ISD::RDPMC_DAG, 0),
  X86_INTRINSIC_DATA(rdrand_16, RDRAND, X86ISD::RDRAND, 0),
  X86_INTRINSIC_DATA(rdrand_32, RDRAND, X86ISD::RDRAND, 0),
  X86_INTRINSIC_DATA(rdrand_64, RDRAND, X86ISD::RDRAND, 0),
  X86_INTRINSIC_DATA(rdseed_16, RDSEED, X86ISD::RDSEED, 0),
  X86_INTRINSIC_DATA(rdseed_32, RDSEED, X86ISD::RDSEED, 0),
  X86_INTRINSIC_DATA(rdseed_64, RDSEED, X86ISD::RDSEED, 0),
  X86_INTRINSIC_DATA(rdtsc,     RDTSC,  X86ISD::RDTSC_DAG, 0),
  X86_INTRINSIC_DATA(rdtscp,    RDTSC,  X86ISD::RDTSCP_DAG, 0),

  X86_INTRINSIC_DATA(subborrow_u32, ADX, X86ISD::SBB, 0),
  X86_INTRINSIC_DATA(subborrow_u64, ADX, X86ISD::SBB, 0),
  X86_INTRINSIC_DATA(xtest,     XTEST,  X86ISD::XTEST,  0),
};

/*
 * Find Intrinsic data by intrinsic ID
 */
static const IntrinsicData* getIntrinsicWithChain(unsigned IntNo) {

  IntrinsicData IntrinsicToFind = {IntNo, INTR_NO_TYPE, 0, 0 };
  const IntrinsicData *Data =  std::lower_bound(std::begin(IntrinsicsWithChain),
                                                std::end(IntrinsicsWithChain),
                                                IntrinsicToFind);
  if (Data != std::end(IntrinsicsWithChain) && *Data == IntrinsicToFind)
    return Data;
  return nullptr;
}

/*
 * IntrinsicsWithoutChain - the table should be sorted by Intrinsic ID - in
 * the alphabetical order.
 */
static const IntrinsicData  IntrinsicsWithoutChain[] = {
  X86_INTRINSIC_DATA(avx2_packssdw,     INTR_TYPE_2OP, X86ISD::PACKSS, 0),
  X86_INTRINSIC_DATA(avx2_packsswb,     INTR_TYPE_2OP, X86ISD::PACKSS, 0),
  X86_INTRINSIC_DATA(avx2_packusdw,     INTR_TYPE_2OP, X86ISD::PACKUS, 0),
  X86_INTRINSIC_DATA(avx2_packuswb,     INTR_TYPE_2OP, X86ISD::PACKUS, 0),
  X86_INTRINSIC_DATA(avx2_permd,        INTR_TYPE_2OP, X86ISD::VPERMV, 0),
  X86_INTRINSIC_DATA(avx2_permps,       INTR_TYPE_2OP, X86ISD::VPERMV, 0),
  X86_INTRINSIC_DATA(avx2_phadd_d,      INTR_TYPE_2OP, X86ISD::HADD, 0),
  X86_INTRINSIC_DATA(avx2_phadd_w,      INTR_TYPE_2OP, X86ISD::HADD, 0),
  X86_INTRINSIC_DATA(avx2_phsub_d,      INTR_TYPE_2OP, X86ISD::HSUB, 0),
  X86_INTRINSIC_DATA(avx2_phsub_w,      INTR_TYPE_2OP, X86ISD::HSUB, 0),
  X86_INTRINSIC_DATA(avx2_pmaxs_b,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmaxs_d,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmaxs_w,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmaxu_b,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmaxu_d,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmaxu_w,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(avx2_pmins_b,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(avx2_pmins_d,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(avx2_pmins_w,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(avx2_pminu_b,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(avx2_pminu_d,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(avx2_pminu_w,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxbd,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxbq,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxbw,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxdq,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxwd,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovsxwq,     INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxbd,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxbq,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxbw,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxdq,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxwd,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmovzxwq,     INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(avx2_pmul_dq,      INTR_TYPE_2OP, X86ISD::PMULDQ, 0),
  X86_INTRINSIC_DATA(avx2_pmulh_w,      INTR_TYPE_2OP, ISD::MULHS, 0),
  X86_INTRINSIC_DATA(avx2_pmulhu_w,     INTR_TYPE_2OP, ISD::MULHU, 0),
  X86_INTRINSIC_DATA(avx2_pmulu_dq,     INTR_TYPE_2OP, X86ISD::PMULUDQ, 0),
  X86_INTRINSIC_DATA(avx2_pshuf_b,      INTR_TYPE_2OP, X86ISD::PSHUFB, 0),
  X86_INTRINSIC_DATA(avx2_psign_b,      INTR_TYPE_2OP, X86ISD::PSIGN, 0),
  X86_INTRINSIC_DATA(avx2_psign_d,      INTR_TYPE_2OP, X86ISD::PSIGN, 0),
  X86_INTRINSIC_DATA(avx2_psign_w,      INTR_TYPE_2OP, X86ISD::PSIGN, 0),
  X86_INTRINSIC_DATA(avx2_psll_d,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(avx2_psll_q,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(avx2_psll_w,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(avx2_pslli_d,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(avx2_pslli_q,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(avx2_pslli_w,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(avx2_psllv_d,      INTR_TYPE_2OP, ISD::SHL, 0),
  X86_INTRINSIC_DATA(avx2_psllv_d_256,  INTR_TYPE_2OP, ISD::SHL, 0),
  X86_INTRINSIC_DATA(avx2_psllv_q,      INTR_TYPE_2OP, ISD::SHL, 0),
  X86_INTRINSIC_DATA(avx2_psllv_q_256,  INTR_TYPE_2OP, ISD::SHL, 0),
  X86_INTRINSIC_DATA(avx2_psra_d,       INTR_TYPE_2OP, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(avx2_psra_w,       INTR_TYPE_2OP, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(avx2_psrai_d,      VSHIFT, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(avx2_psrai_w,      VSHIFT, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(avx2_psrav_d,      INTR_TYPE_2OP, ISD::SRA, 0),
  X86_INTRINSIC_DATA(avx2_psrav_d_256,  INTR_TYPE_2OP, ISD::SRA, 0),
  X86_INTRINSIC_DATA(avx2_psrl_d,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(avx2_psrl_q,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(avx2_psrl_w,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(avx2_psrli_d,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(avx2_psrli_q,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(avx2_psrli_w,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(avx2_psrlv_d,      INTR_TYPE_2OP, ISD::SRL, 0),
  X86_INTRINSIC_DATA(avx2_psrlv_d_256,  INTR_TYPE_2OP, ISD::SRL, 0),
  X86_INTRINSIC_DATA(avx2_psrlv_q,      INTR_TYPE_2OP, ISD::SRL, 0),
  X86_INTRINSIC_DATA(avx2_psrlv_q_256,  INTR_TYPE_2OP, ISD::SRL, 0),
  X86_INTRINSIC_DATA(avx2_psubus_b,     INTR_TYPE_2OP, X86ISD::SUBUS, 0),
  X86_INTRINSIC_DATA(avx2_psubus_w,     INTR_TYPE_2OP, X86ISD::SUBUS, 0),
  X86_INTRINSIC_DATA(avx2_vperm2i128,   INTR_TYPE_3OP, X86ISD::VPERM2X128, 0),
  X86_INTRINSIC_DATA(avx512_exp2_pd,    INTR_TYPE_1OP_MASK_RM,X86ISD::EXP2, 0),
  X86_INTRINSIC_DATA(avx512_exp2_ps,    INTR_TYPE_1OP_MASK_RM,X86ISD::EXP2, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_b_128,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_b_256,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_b_512,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_d_128,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_d_256,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_d_512,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_q_128,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_q_256,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_q_512,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_w_128,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_w_256,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_cmp_w_512,     CMP_MASK_CC,  X86ISD::CMPM, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_d_128,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_d_256,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_d_512,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_pd_128, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_pd_256, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_pd_512, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_ps_128, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_ps_256, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_ps_512, COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_q_128,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_q_256,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_compress_q_512,  COMPRESS_TO_REG,
                     X86ISD::COMPRESS, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_b_128,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_b_256,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_b_512,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_d_128,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_d_256,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_d_512,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_q_128,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_q_256,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_q_512,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_w_128,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_w_256,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpeq_w_512,  CMP_MASK,  X86ISD::PCMPEQM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_b_128,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_b_256,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_b_512,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_d_128,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_d_256,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_d_512,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_q_128,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_q_256,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_q_512,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_w_128,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_w_256,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_pcmpgt_w_512,  CMP_MASK,  X86ISD::PCMPGTM, 0),
  X86_INTRINSIC_DATA(avx512_mask_psll_d,        INTR_TYPE_2OP_MASK, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(avx512_mask_psll_q,        INTR_TYPE_2OP_MASK, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(avx512_mask_pslli_d,       VSHIFT_MASK, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(avx512_mask_pslli_q,       VSHIFT_MASK, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(avx512_mask_psra_d,        INTR_TYPE_2OP_MASK, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(avx512_mask_psra_q,        INTR_TYPE_2OP_MASK, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrai_d,       VSHIFT_MASK, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrai_q,       VSHIFT_MASK, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrl_d,        INTR_TYPE_2OP_MASK, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrl_q,        INTR_TYPE_2OP_MASK, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrli_d,       VSHIFT_MASK, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(avx512_mask_psrli_q,       VSHIFT_MASK, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_b_128,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_b_256,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_b_512,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_d_128,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_d_256,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_d_512,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_q_128,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_q_256,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_q_512,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_w_128,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_w_256,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_mask_ucmp_w_512,    CMP_MASK_CC,  X86ISD::CMPMU, 0),
  X86_INTRINSIC_DATA(avx512_rcp28_pd,   INTR_TYPE_1OP_MASK_RM,X86ISD::RCP28, 0),
  X86_INTRINSIC_DATA(avx512_rcp28_ps,   INTR_TYPE_1OP_MASK_RM,X86ISD::RCP28, 0),
  X86_INTRINSIC_DATA(avx512_rcp28_sd,   INTR_TYPE_SCALAR_MASK_RM,X86ISD::RCP28, 0),
  X86_INTRINSIC_DATA(avx512_rcp28_ss,   INTR_TYPE_SCALAR_MASK_RM,X86ISD::RCP28, 0),
  X86_INTRINSIC_DATA(avx512_rsqrt28_pd, INTR_TYPE_1OP_MASK_RM,X86ISD::RSQRT28, 0),
  X86_INTRINSIC_DATA(avx512_rsqrt28_ps, INTR_TYPE_1OP_MASK_RM,X86ISD::RSQRT28, 0),
  X86_INTRINSIC_DATA(avx512_rsqrt28_sd, INTR_TYPE_SCALAR_MASK_RM,X86ISD::RSQRT28, 0),
  X86_INTRINSIC_DATA(avx512_rsqrt28_ss, INTR_TYPE_SCALAR_MASK_RM,X86ISD::RSQRT28, 0),
  X86_INTRINSIC_DATA(avx_hadd_pd_256,   INTR_TYPE_2OP, X86ISD::FHADD, 0),
  X86_INTRINSIC_DATA(avx_hadd_ps_256,   INTR_TYPE_2OP, X86ISD::FHADD, 0),
  X86_INTRINSIC_DATA(avx_hsub_pd_256,   INTR_TYPE_2OP, X86ISD::FHSUB, 0),
  X86_INTRINSIC_DATA(avx_hsub_ps_256,   INTR_TYPE_2OP, X86ISD::FHSUB, 0),
  X86_INTRINSIC_DATA(avx_max_pd_256,    INTR_TYPE_2OP, X86ISD::FMAX, 0),
  X86_INTRINSIC_DATA(avx_max_ps_256,    INTR_TYPE_2OP, X86ISD::FMAX, 0),
  X86_INTRINSIC_DATA(avx_min_pd_256,    INTR_TYPE_2OP, X86ISD::FMIN, 0),
  X86_INTRINSIC_DATA(avx_min_ps_256,    INTR_TYPE_2OP, X86ISD::FMIN, 0),
  X86_INTRINSIC_DATA(avx_sqrt_pd_256,   INTR_TYPE_1OP, ISD::FSQRT, 0),
  X86_INTRINSIC_DATA(avx_sqrt_ps_256,   INTR_TYPE_1OP, ISD::FSQRT, 0),
  X86_INTRINSIC_DATA(avx_vperm2f128_pd_256, INTR_TYPE_3OP, X86ISD::VPERM2X128, 0),
  X86_INTRINSIC_DATA(avx_vperm2f128_ps_256, INTR_TYPE_3OP, X86ISD::VPERM2X128, 0),
  X86_INTRINSIC_DATA(avx_vperm2f128_si_256, INTR_TYPE_3OP, X86ISD::VPERM2X128, 0),
  X86_INTRINSIC_DATA(sse2_comieq_sd,    COMI, X86ISD::COMI, ISD::SETEQ),
  X86_INTRINSIC_DATA(sse2_comige_sd,    COMI, X86ISD::COMI, ISD::SETGE),
  X86_INTRINSIC_DATA(sse2_comigt_sd,    COMI, X86ISD::COMI, ISD::SETGT),
  X86_INTRINSIC_DATA(sse2_comile_sd,    COMI, X86ISD::COMI, ISD::SETLE),
  X86_INTRINSIC_DATA(sse2_comilt_sd,    COMI, X86ISD::COMI, ISD::SETLT),
  X86_INTRINSIC_DATA(sse2_comineq_sd,   COMI, X86ISD::COMI, ISD::SETNE),
  X86_INTRINSIC_DATA(sse2_max_pd,       INTR_TYPE_2OP, X86ISD::FMAX, 0),
  X86_INTRINSIC_DATA(sse2_min_pd,       INTR_TYPE_2OP, X86ISD::FMIN, 0),
  X86_INTRINSIC_DATA(sse2_packssdw_128, INTR_TYPE_2OP, X86ISD::PACKSS, 0),
  X86_INTRINSIC_DATA(sse2_packsswb_128, INTR_TYPE_2OP, X86ISD::PACKSS, 0),
  X86_INTRINSIC_DATA(sse2_packuswb_128, INTR_TYPE_2OP, X86ISD::PACKUS, 0),
  X86_INTRINSIC_DATA(sse2_pmaxs_w,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(sse2_pmaxu_b,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(sse2_pmins_w,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(sse2_pminu_b,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(sse2_pmulh_w,      INTR_TYPE_2OP, ISD::MULHS, 0),
  X86_INTRINSIC_DATA(sse2_pmulhu_w,     INTR_TYPE_2OP, ISD::MULHU, 0),
  X86_INTRINSIC_DATA(sse2_pmulu_dq,     INTR_TYPE_2OP, X86ISD::PMULUDQ, 0),
  X86_INTRINSIC_DATA(sse2_pshuf_d,      INTR_TYPE_2OP, X86ISD::PSHUFD, 0),
  X86_INTRINSIC_DATA(sse2_pshufh_w,     INTR_TYPE_2OP, X86ISD::PSHUFHW, 0),
  X86_INTRINSIC_DATA(sse2_pshufl_w,     INTR_TYPE_2OP, X86ISD::PSHUFLW, 0),
  X86_INTRINSIC_DATA(sse2_psll_d,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(sse2_psll_q,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(sse2_psll_w,       INTR_TYPE_2OP, X86ISD::VSHL, 0),
  X86_INTRINSIC_DATA(sse2_pslli_d,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(sse2_pslli_q,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(sse2_pslli_w,      VSHIFT, X86ISD::VSHLI, 0),
  X86_INTRINSIC_DATA(sse2_psra_d,       INTR_TYPE_2OP, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(sse2_psra_w,       INTR_TYPE_2OP, X86ISD::VSRA, 0),
  X86_INTRINSIC_DATA(sse2_psrai_d,      VSHIFT, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(sse2_psrai_w,      VSHIFT, X86ISD::VSRAI, 0),
  X86_INTRINSIC_DATA(sse2_psrl_d,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(sse2_psrl_q,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(sse2_psrl_w,       INTR_TYPE_2OP, X86ISD::VSRL, 0),
  X86_INTRINSIC_DATA(sse2_psrli_d,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(sse2_psrli_q,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(sse2_psrli_w,      VSHIFT, X86ISD::VSRLI, 0),
  X86_INTRINSIC_DATA(sse2_psubus_b,     INTR_TYPE_2OP, X86ISD::SUBUS, 0),
  X86_INTRINSIC_DATA(sse2_psubus_w,     INTR_TYPE_2OP, X86ISD::SUBUS, 0),
  X86_INTRINSIC_DATA(sse2_sqrt_pd,      INTR_TYPE_1OP, ISD::FSQRT, 0),
  X86_INTRINSIC_DATA(sse2_ucomieq_sd,   COMI, X86ISD::UCOMI, ISD::SETEQ),
  X86_INTRINSIC_DATA(sse2_ucomige_sd,   COMI, X86ISD::UCOMI, ISD::SETGE),
  X86_INTRINSIC_DATA(sse2_ucomigt_sd,   COMI, X86ISD::UCOMI, ISD::SETGT),
  X86_INTRINSIC_DATA(sse2_ucomile_sd,   COMI, X86ISD::UCOMI, ISD::SETLE),
  X86_INTRINSIC_DATA(sse2_ucomilt_sd,   COMI, X86ISD::UCOMI, ISD::SETLT),
  X86_INTRINSIC_DATA(sse2_ucomineq_sd,  COMI, X86ISD::UCOMI, ISD::SETNE),
  X86_INTRINSIC_DATA(sse3_hadd_pd,      INTR_TYPE_2OP, X86ISD::FHADD, 0),
  X86_INTRINSIC_DATA(sse3_hadd_ps,      INTR_TYPE_2OP, X86ISD::FHADD, 0),
  X86_INTRINSIC_DATA(sse3_hsub_pd,      INTR_TYPE_2OP, X86ISD::FHSUB, 0),
  X86_INTRINSIC_DATA(sse3_hsub_ps,      INTR_TYPE_2OP, X86ISD::FHSUB, 0),
  X86_INTRINSIC_DATA(sse41_insertps,    INTR_TYPE_3OP, X86ISD::INSERTPS, 0),
  X86_INTRINSIC_DATA(sse41_packusdw,    INTR_TYPE_2OP, X86ISD::PACKUS, 0),
  X86_INTRINSIC_DATA(sse41_pmaxsb,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(sse41_pmaxsd,      INTR_TYPE_2OP, X86ISD::SMAX, 0),
  X86_INTRINSIC_DATA(sse41_pmaxud,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(sse41_pmaxuw,      INTR_TYPE_2OP, X86ISD::UMAX, 0),
  X86_INTRINSIC_DATA(sse41_pminsb,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(sse41_pminsd,      INTR_TYPE_2OP, X86ISD::SMIN, 0),
  X86_INTRINSIC_DATA(sse41_pminud,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(sse41_pminuw,      INTR_TYPE_2OP, X86ISD::UMIN, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxbd,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxbq,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxbw,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxdq,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxwd,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovsxwq,    INTR_TYPE_1OP, X86ISD::VSEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxbd,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxbq,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxbw,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxdq,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxwd,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmovzxwq,    INTR_TYPE_1OP, X86ISD::VZEXT, 0),
  X86_INTRINSIC_DATA(sse41_pmuldq,      INTR_TYPE_2OP, X86ISD::PMULDQ, 0),
  X86_INTRINSIC_DATA(sse_comieq_ss,     COMI, X86ISD::COMI, ISD::SETEQ),
  X86_INTRINSIC_DATA(sse_comige_ss,     COMI, X86ISD::COMI, ISD::SETGE),
  X86_INTRINSIC_DATA(sse_comigt_ss,     COMI, X86ISD::COMI, ISD::SETGT),
  X86_INTRINSIC_DATA(sse_comile_ss,     COMI, X86ISD::COMI, ISD::SETLE),
  X86_INTRINSIC_DATA(sse_comilt_ss,     COMI, X86ISD::COMI, ISD::SETLT),
  X86_INTRINSIC_DATA(sse_comineq_ss,    COMI, X86ISD::COMI, ISD::SETNE),
  X86_INTRINSIC_DATA(sse_max_ps,        INTR_TYPE_2OP, X86ISD::FMAX, 0),
  X86_INTRINSIC_DATA(sse_min_ps,        INTR_TYPE_2OP, X86ISD::FMIN, 0),
  X86_INTRINSIC_DATA(sse_sqrt_ps,       INTR_TYPE_1OP, ISD::FSQRT, 0),
  X86_INTRINSIC_DATA(sse_ucomieq_ss,    COMI, X86ISD::UCOMI, ISD::SETEQ),
  X86_INTRINSIC_DATA(sse_ucomige_ss,    COMI, X86ISD::UCOMI, ISD::SETGE),
  X86_INTRINSIC_DATA(sse_ucomigt_ss,    COMI, X86ISD::UCOMI, ISD::SETGT),
  X86_INTRINSIC_DATA(sse_ucomile_ss,    COMI, X86ISD::UCOMI, ISD::SETLE),
  X86_INTRINSIC_DATA(sse_ucomilt_ss,    COMI, X86ISD::UCOMI, ISD::SETLT),
  X86_INTRINSIC_DATA(sse_ucomineq_ss,   COMI, X86ISD::UCOMI, ISD::SETNE),
  X86_INTRINSIC_DATA(ssse3_phadd_d_128, INTR_TYPE_2OP, X86ISD::HADD, 0),
  X86_INTRINSIC_DATA(ssse3_phadd_w_128, INTR_TYPE_2OP, X86ISD::HADD, 0),
  X86_INTRINSIC_DATA(ssse3_phsub_d_128, INTR_TYPE_2OP, X86ISD::HSUB, 0),
  X86_INTRINSIC_DATA(ssse3_phsub_w_128, INTR_TYPE_2OP, X86ISD::HSUB, 0),
  X86_INTRINSIC_DATA(ssse3_pshuf_b_128, INTR_TYPE_2OP, X86ISD::PSHUFB, 0),
  X86_INTRINSIC_DATA(ssse3_psign_b_128, INTR_TYPE_2OP, X86ISD::PSIGN, 0),
  X86_INTRINSIC_DATA(ssse3_psign_d_128, INTR_TYPE_2OP, X86ISD::PSIGN, 0),
  X86_INTRINSIC_DATA(ssse3_psign_w_128, INTR_TYPE_2OP, X86ISD::PSIGN, 0)
};

/*
 * Retrieve data for Intrinsic without chain.
 * Return nullptr if intrinsic is not defined in the table.
 */
static const IntrinsicData* getIntrinsicWithoutChain(unsigned IntNo) {
  IntrinsicData IntrinsicToFind = { IntNo, INTR_NO_TYPE, 0, 0 };
  const IntrinsicData *Data = std::lower_bound(std::begin(IntrinsicsWithoutChain),
                                               std::end(IntrinsicsWithoutChain),
                                               IntrinsicToFind);
  if (Data != std::end(IntrinsicsWithoutChain) && *Data == IntrinsicToFind)
    return Data;
  return nullptr;
}

static void verifyIntrinsicTables() {
  assert(std::is_sorted(std::begin(IntrinsicsWithoutChain),
                        std::end(IntrinsicsWithoutChain)) &&
         std::is_sorted(std::begin(IntrinsicsWithChain),
                        std::end(IntrinsicsWithChain)) &&
         "Intrinsic data tables should be sorted by Intrinsic ID");
}

} // End llvm namespace

#endif
