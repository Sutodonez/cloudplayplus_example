
/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_18020f8f4(char *param_1,undefined8 *param_2,int param_3,longlong *param_4,longlong param_5,
                  longlong param_6)

{
  undefined1 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  char cVar7;
  longlong *plVar8;
  undefined8 uVar9;
  char *pcVar10;
  undefined8 *puVar11;
  undefined1 auStack_178 [36];
  int local_154;
  undefined8 *local_150;
  longlong *local_148;
  longlong *local_140;
  longlong *local_138 [2];
  code *local_128;
  code *local_120;
  undefined8 local_118;
  longlong *local_110;
  longlong *local_108;
  undefined8 local_100;
  char *local_f8;
  undefined4 local_f0;
  char *local_e8;
  undefined1 *puStack_e0;
  code *local_d8;
  undefined1 *puStack_d0;
  undefined1 *local_c8;
  undefined1 *puStack_c0;
  undefined1 *local_b8;
  undefined1 *puStack_b0;
  undefined1 *local_a8;
  undefined1 *puStack_a0;
  int local_90;
  longlong local_88;
  longlong lStack_80;
  longlong local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  ulonglong local_60;
  
  local_60 = DAT_1812df780 ^ (ulonglong)auStack_178;
  cVar7 = FUN_18007327e();
  if (cVar7 == '\0') {
    local_e8 = "..\\..\\p2p\\base\\p2p_transport_channel.cc";
    puStack_e0 = (undefined1 *)CONCAT44(puStack_e0._4_4_,0x6ad1);
    FUN_1800c550c(&DAT_180ff37d8,&local_e8,"RandomSymmericPunchToCone");
  }
  local_100 = 0;
  plVar8 = (longlong *)FUN_180e395c0(0x70);
  *plVar8 = (longlong)plVar8;
  plVar8[1] = (longlong)plVar8;
  plVar8[2] = (longlong)plVar8;
  *(undefined2 *)(plVar8 + 3) = 0x101;
  *(undefined8 *)(param_1 + 0xa18) = *(undefined8 *)(param_1 + 0xa08);
  local_108 = plVar8;
  if (*(longlong *)(param_1 + 0x730) == param_6) {
    FUN_180211c98(param_1);
    cVar7 = FUN_18007327e();
    if (cVar7 == '\0') {
      FUN_180074e0e(param_4[1] + -0x1c0,&local_e8);
      local_f8 = "..\\..\\p2p\\base\\p2p_transport_channel.cc";
      local_f0 = 0x6b29;
      FUN_1800c550c(&DAT_180ff3b82,&local_f8,"remote_stun_candidate.address:",&local_e8);
      if ((undefined1 *)0xf < puStack_d0) {
        FUN_180073636(local_e8,puStack_d0 + 1);
      }
    }
    local_e8 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_e0 = &DAT_aaaaaaaaaaaaaaaa;
    local_140 = param_4;
    FUN_1800aac84(&local_108,&local_e8,param_4[1] + -0x1c0);
    local_154 = param_3;
    local_150 = param_2;
    if (0 < param_3) {
      local_148 = (longlong *)(param_1 + 0x9b8);
      do {
        local_f8 = &DAT_aaaaaaaaaaaaaaaa;
        plVar8 = *(longlong **)(param_1 + 0x780);
        uVar9 = FUN_180074b60(param_2);
        FUN_180074a38(&local_e8,uVar9,0);
        pcVar10 = (char *)(**(code **)(*plVar8 + 8))(plVar8,&local_e8,0,0);
        if ((undefined1 *)0xf < puStack_d0) {
          FUN_180073636(local_e8,puStack_d0 + 1);
        }
        local_f8 = pcVar10;
        if (pcVar10 == (char *)0x0) {
          cVar7 = FUN_180077464();
          if (cVar7 == '\0') {
            local_e8 = "..\\..\\p2p\\base\\p2p_transport_channel.cc";
            puStack_e0 = (undefined1 *)CONCAT44(puStack_e0._4_4_,0x6b6b);
            FUN_1800c550c(&DAT_180ff37d8,&local_e8);
          }
        }
        else {
          puVar1 = *(undefined1 **)(param_1 + 0x788);
          local_d8 = FUN_180211ec4;
          puStack_d0 = (undefined1 *)((ulonglong)puStack_d0 & 0xffffffff00000000);
          local_e8 = &LAB_1800aaa7a;
          puStack_e0 = puVar1;
          FUN_180ba3fd0(pcVar10 + 0x40,*(undefined8 *)(pcVar10 + 0x40));
          (**(code **)(puVar1 + 8))(puVar1,pcVar10 + 0x30);
          if (*(longlong **)(param_1 + 0x9c0) == *(longlong **)(param_1 + 0x9c8)) {
            FUN_18007a412(local_148);
          }
          else {
            **(longlong **)(param_1 + 0x9c0) = (longlong)local_f8;
            *(longlong *)(param_1 + 0x9c0) = *(longlong *)(param_1 + 0x9c0) + 8;
          }
          param_2 = local_150;
        }
        param_3 = param_3 + -1;
      } while (param_3 != 0);
    }
    local_110 = (longlong *)*local_108;
    local_148 = local_108;
    if (local_110 != local_108) {
      do {
        local_a8 = &DAT_aaaaaaaaaaaaaaaa;
        puStack_a0 = &DAT_aaaaaaaaaaaaaaaa;
        local_b8 = &DAT_aaaaaaaaaaaaaaaa;
        puStack_b0 = &DAT_aaaaaaaaaaaaaaaa;
        local_c8 = &DAT_aaaaaaaaaaaaaaaa;
        puStack_c0 = &DAT_aaaaaaaaaaaaaaaa;
        local_d8 = (code *)&DAT_aaaaaaaaaaaaaaaa;
        puStack_d0 = &DAT_aaaaaaaaaaaaaaaa;
        local_e8 = &DAT_aaaaaaaaaaaaaaaa;
        puStack_e0 = &DAT_aaaaaaaaaaaaaaaa;
        FUN_180074a82(&local_e8,local_110 + 4);
        puVar2 = *(undefined8 **)(param_1 + 0x9c0);
        for (puVar11 = *(undefined8 **)(param_1 + 0x9b8); puVar11 != puVar2; puVar11 = puVar11 + 1)
        {
          local_118 = *puVar11;
          FUN_180216664(param_1 + 0x738,&local_f8,&local_118);
          FUN_180074ab4(local_f8 + 0x28,&local_e8);
        }
        if ((undefined1 *)0xf < puStack_d0) {
          FUN_180073636(local_e8,puStack_d0 + 1);
        }
        FUN_18007bf72(&local_110);
      } while (local_110 != local_148);
    }
    plVar8 = local_140 + 1;
    cVar7 = FUN_18007327e();
    if (cVar7 == '\0') {
      local_e8 = "..\\..\\p2p\\base\\p2p_transport_channel.cc";
      puStack_e0 = (undefined1 *)CONCAT44(puStack_e0._4_4_,0x6bd1);
      FUN_1800c550c(&DAT_180ff3ee6,&local_e8,"punch_socket_connections_.size: ",
                    *(undefined8 *)(param_1 + 0x740));
    }
    FUN_1802167f6(param_1 + 0x748,param_1 + 0x738);
    plVar3 = *(longlong **)(param_1 + 0xa20);
    local_e8 = param_1;
    FUN_180074a82(&puStack_e0,local_150);
    local_90 = local_154;
    local_88 = 0;
    lStack_80 = 0;
    local_78 = 0;
    FUN_180b72c80(&local_88,(local_140[1] - *local_140 >> 3) * -0xed7303b5cc0ed73,local_140,plVar8);
    local_70 = param_5;
    uStack_68 = param_6;
    plVar8 = (longlong *)FUN_180e395c0(0x88);
    *plVar8 = (longlong)local_e8;
    FUN_180074a82(plVar8 + 1,&puStack_e0);
    lVar6 = local_78;
    lVar5 = lStack_80;
    lVar4 = local_88;
    *(int *)(plVar8 + 0xb) = local_90;
    local_78 = 0;
    local_88 = 0;
    lStack_80 = 0;
    plVar8[0xc] = lVar4;
    plVar8[0xd] = lVar5;
    plVar8[0xe] = lVar6;
    *(undefined4 *)(plVar8 + 0xf) = (undefined4)local_70;
    *(undefined4 *)((longlong)plVar8 + 0x7c) = local_70._4_4_;
    *(undefined4 *)(plVar8 + 0x10) = (undefined4)uStack_68;
    *(undefined4 *)((longlong)plVar8 + 0x84) = uStack_68._4_4_;
    local_128 = FUN_1802169f4;
    local_120 = FUN_180216971;
    local_138[0] = plVar8;
    (**(code **)(*plVar3 + 0x10))(plVar3,local_138,param_5 * 1000);
    FUN_180aea700(&local_88);
    if ((undefined1 *)0xf < local_c8) {
      FUN_180073636(puStack_e0,local_c8 + 1);
    }
    plVar8 = (longlong *)local_108[1];
    param_2 = local_150;
  }
  FUN_1800a8b98(&local_108,&local_108,plVar8);
  thunk_FUN_180e40c7c(local_108,0x70);
  if (0xf < (ulonglong)param_2[3]) {
    FUN_180073636(*param_2,param_2[3] + 1);
  }
  param_2[2] = 0;
  param_2[3] = 0xf;
  *(undefined1 *)param_2 = 0;
}

