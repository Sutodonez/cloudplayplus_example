
/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180207a5e(longlong *param_1)

{
  undefined8 *puVar1;
  code *pcVar2;
  int *piVar3;
  longlong *plVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  longlong *plVar12;
  int iVar13;
  undefined1 auStack_228 [32];
  longlong **local_208;
  longlong **local_200;
  undefined8 *local_1f8 [2];
  code *local_1e8;
  undefined1 *local_1e0;
  undefined8 *local_1d8 [2];
  code *local_1c8;
  code *local_1c0;
  undefined8 *local_1b8;
  undefined8 local_1b0;
  longlong *local_1a8;
  longlong local_1a0;
  longlong *local_198;
  longlong local_190;
  undefined1 local_188 [8];
  undefined8 *local_180;
  undefined8 *local_178;
  undefined8 local_170;
  longlong *local_168;
  longlong local_160;
  longlong *local_158;
  longlong local_150;
  undefined8 *local_148;
  char *local_140;
  undefined8 local_138;
  longlong local_130;
  undefined8 local_128;
  longlong local_120;
  undefined8 local_118;
  longlong *local_110;
  longlong local_108;
  longlong *local_100;
  longlong local_f8;
  int *local_f0;
  undefined1 local_e8 [16];
  undefined8 local_d8;
  undefined8 uStack_d0;
  longlong *local_c8;
  longlong *plStack_c0;
  longlong lStack_b8;
  undefined8 uStack_b0;
  ulonglong uStack_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  undefined8 local_60;
  ulonglong local_50;
  
  local_50 = DAT_1812df780 ^ (ulonglong)auStack_228;
  plVar11 = param_1 + 0x98;
  if ((param_1[0x9a] == 0) || (param_1[0x9e] == 0)) {
    cVar5 = FUN_180077464();
    if (cVar5 == '\0') {
      local_200 = (longlong **)(param_1 + 0x9c);
      local_c8 = (longlong *)0x18104b8be;
      plStack_c0 = (longlong *)CONCAT44(plStack_c0._4_4_,0x1dfb);
      local_208 = (longlong **)0x18104bbb4;
      FUN_1800c550c("\r\t\n\t\n",&local_c8,
                    "Cannot gather candidates because ICE parameters are empty ufrag: ",plVar11);
    }
  }
  else {
    plVar12 = param_1 + 0x9c;
    if (param_1[0x84] != param_1[0x85]) {
      local_100 = plVar12;
      if (0xf < (ulonglong)param_1[0x9f]) {
        local_100 = (longlong *)param_1[0x9c];
      }
      local_110 = plVar11;
      if (0xf < (ulonglong)param_1[0x9b]) {
        local_110 = (longlong *)param_1[0x98];
      }
      local_130 = *(longlong *)(param_1[0x85] + -8);
      local_118 = *(undefined8 *)(local_130 + 0x210);
      if (*(ulonglong *)(local_130 + 0x218) < 0x10) {
        local_120 = local_130 + 0x200;
      }
      else {
        local_120 = *(longlong *)(local_130 + 0x200);
      }
      local_128 = *(undefined8 *)(local_130 + 0x1f0);
      if (*(ulonglong *)(local_130 + 0x1f8) < 0x10) {
        local_130 = local_130 + 0x1e0;
      }
      else {
        local_130 = *(longlong *)(local_130 + 0x1e0);
      }
      local_108 = param_1[0x9a];
      local_f8 = param_1[0x9e];
      cVar5 = FUN_180202da4(&local_130,&local_120,&local_110,&local_100);
      if (cVar5 == '\0') {
      }
    }
    if ((int)param_1[0xa6] != 1) {
      *(undefined4 *)(param_1 + 0xa6) = 1;
      plVar8 = *(longlong **)param_1[0x32];
      param_1[0x34] = (longlong)plVar8;
      if (plVar8 != (longlong *)param_1[0x32]) {
        do {
          param_1[0x34] = *plVar8;
          (*(code *)plVar8[2])(plVar8 + 2,param_1);
          plVar8 = (longlong *)param_1[0x34];
        } while (plVar8 != (longlong *)param_1[0x32]);
      }
    }
    if (param_1[0x84] != param_1[0x85]) {
      cVar5 = (**(code **)(*param_1 + 0x10))();
      iVar13 = 1;
      if (cVar5 == '\0') {
        if (param_1[0x84] == param_1[0x85]) {
          plVar8 = (longlong *)0x0;
        }
        else {
          plVar8 = *(longlong **)(param_1[0x85] + -8);
        }
        bVar6 = (**(code **)(*plVar8 + 0x20))();
        iVar13 = (uint)(bVar6 ^ 1) * 2;
      }
      local_140 = "WebRTC.PeerConnection.IceRestartState";
      local_138 = 0x25;
      lVar9 = FUN_18008a1dd(&local_140,3);
      if (lVar9 != 0) {
        FUN_18008a302(lVar9,iVar13);
      }
    }
    puVar1 = (undefined8 *)param_1[0x85];
    for (puVar10 = (undefined8 *)param_1[0x84]; puVar10 != puVar1; puVar10 = puVar10 + 1) {
      cVar5 = (**(code **)(*(longlong *)*puVar10 + 0x38))();
      if (cVar5 == '\0') {
        (**(code **)(*(longlong *)*puVar10 + 0x18))();
      }
    }
    local_148 = (undefined8 *)&DAT_aaaaaaaaaaaaaaaa;
    local_150 = param_1[0x9e];
    local_158 = plVar12;
    if (0xf < (ulonglong)param_1[0x9f]) {
      local_158 = (longlong *)param_1[0x9c];
    }
    lVar9 = param_1[0x7f];
    local_160 = param_1[0x9a];
    local_168 = plVar11;
    if (0xf < (ulonglong)param_1[0x9b]) {
      local_168 = (longlong *)param_1[0x98];
    }
    uVar7 = (**(code **)(*param_1 + 0x58))(param_1);
    local_178 = (undefined8 *)(**(code **)(*param_1 + 8))(param_1);
    local_170 = local_178[2];
    if (0xf < (ulonglong)local_178[3]) {
      local_178 = (undefined8 *)*local_178;
    }
    local_200 = &local_158;
    local_208 = &local_168;
    FUN_180114f74(lVar9,&local_148,&local_178,uVar7);
    puVar10 = local_148;
    if (local_148 == (undefined8 *)0x0) {
      local_190 = param_1[0x9e];
      local_198 = plVar12;
      if (0xf < (ulonglong)param_1[0x9f]) {
        local_198 = (longlong *)param_1[0x9c];
      }
      lVar9 = param_1[0x7f];
      local_1a0 = param_1[0x9a];
      local_1a8 = plVar11;
      if (0xf < (ulonglong)param_1[0x9b]) {
        local_1a8 = (longlong *)param_1[0x98];
      }
      uVar7 = (**(code **)(*param_1 + 0x58))(param_1);
      local_1b8 = (undefined8 *)(**(code **)(*param_1 + 8))(param_1);
      local_1b0 = local_1b8[2];
      if (0xf < (ulonglong)local_1b8[3]) {
        local_1b8 = (undefined8 *)*local_1b8;
      }
      local_200 = &local_198;
      local_208 = &local_1a8;
      FUN_180114ec8(lVar9,local_188,&local_1b8,uVar7);
      FUN_1802047be(param_1,local_188);
      *(longlong *)(*(longlong *)(param_1[0x85] + -8) + 0x228) = param_1[0xa5];
      (**(code **)(**(longlong **)(param_1[0x85] + -8) + 0x10))();
    }
    else {
      local_148[0x45] = param_1[0xa5];
      local_148 = (undefined8 *)0x0;
      local_180 = puVar10;
      FUN_1802047be(param_1);
      (**(code **)(**(longlong **)(param_1[0x85] + -8) + 0x60))
                (*(longlong **)(param_1[0x85] + -8),&local_c8);
      FUN_180204f5e(param_1);
      FUN_180aea700(&local_c8);
      (**(code **)(**(longlong **)(param_1[0x85] + -8) + 0x58))
                (*(longlong **)(param_1[0x85] + -8),&local_c8);
      plVar4 = plStack_c0;
      for (plVar8 = local_c8; plVar8 != plVar4; plVar8 = plVar8 + 1) {
        FUN_180204abe(param_1);
      }
      if (local_c8 != (longlong *)0x0) {
        FUN_180073636(local_c8,lStack_b8 - (longlong)local_c8);
      }
      cVar5 = (**(code **)(**(longlong **)(param_1[0x85] + -8) + 0x68))();
      if (cVar5 != '\0') {
        FUN_1802052ce(param_1);
      }
    }
    cVar5 = FUN_18007327e();
    if (cVar5 == '\0') {
      local_c8 = (longlong *)0x18104b8be;
      plStack_c0 = (longlong *)CONCAT44(plStack_c0._4_4_,0x1ff9);
      FUN_1800c550c(&DAT_180ff3863,&local_c8,"Enhanced Hole Punching ",(char)param_1[0xbf]);
    }
    if ((char)param_1[0xbf] == '\0') {
      local_60 = 0xaa00000000000000;
      local_c8 = (longlong *)0x0;
      plStack_c0 = (longlong *)0x0;
      lStack_b8 = 0;
      uStack_b0 = 0;
      uStack_a8 = 0;
      local_a0 = 0;
      uStack_98 = 0;
      local_90 = 0;
      uStack_88 = 0;
      local_80 = 0;
      local_78 = 0;
      uStack_70 = 0;
      local_68 = 0x400000004;
      plVar11 = *(longlong **)param_1[0x44];
      param_1[0x46] = (longlong)plVar11;
      if (plVar11 != (longlong *)param_1[0x44]) {
        do {
          param_1[0x46] = *plVar11;
          (*(code *)plVar11[2])(plVar11 + 2,param_1,&local_c8);
          plVar11 = (longlong *)param_1[0x46];
        } while (plVar11 != (longlong *)param_1[0x44]);
      }
      FUN_180aea700(&local_80);
      FUN_180aea700(&uStack_98);
      FUN_180aea7b0(&uStack_b0);
      FUN_180aea7b0(&local_c8);
    }
    else {
      cVar5 = FUN_18007327e();
      if (cVar5 == '\0') {
        local_c8 = (longlong *)0x18104b8be;
        plStack_c0 = (longlong *)CONCAT44(plStack_c0._4_4_,0x2011);
        FUN_1800c550c(&DAT_180ff37d8,&local_c8,"post NatTraversal task");
      }
      plVar8 = (longlong *)param_1[0x82];
      plStack_c0 = (longlong *)0x0;
      lStack_b8 = 0;
      uStack_b0 = 0;
      uStack_a8 = 0;
      if (0xf < (ulonglong)param_1[0x9b]) {
        plVar11 = (longlong *)param_1[0x98];
      }
      local_c8 = param_1;
      FUN_180a2e3a0(&plStack_c0,plVar11,param_1[0x9a]);
      local_90 = 0;
      uStack_88 = 0;
      local_a0 = 0;
      uStack_98 = 0;
      if (0xf < (ulonglong)param_1[0x9f]) {
        plVar12 = (longlong *)param_1[0x9c];
      }
      FUN_180a2e3a0(&local_a0,plVar12,param_1[0x9e]);
      local_1f8[0] = (undefined8 *)FUN_180e395c0(0x48);
      *local_1f8[0] = local_c8;
      local_1f8[0][3] = uStack_b0;
      local_1f8[0][4] = uStack_a8;
      local_1f8[0][1] = plStack_c0;
      local_1f8[0][2] = lStack_b8;
      uStack_b0 = 0;
      uStack_a8 = 0xf;
      plStack_c0 = (longlong *)((ulonglong)plStack_c0 & 0xffffffffffffff00);
      *(undefined4 *)(local_1f8[0] + 7) = (undefined4)local_90;
      *(undefined4 *)((longlong)local_1f8[0] + 0x3c) = local_90._4_4_;
      *(undefined4 *)(local_1f8[0] + 8) = (undefined4)uStack_88;
      *(undefined4 *)((longlong)local_1f8[0] + 0x44) = uStack_88._4_4_;
      *(undefined4 *)(local_1f8[0] + 5) = (undefined4)local_a0;
      *(undefined4 *)((longlong)local_1f8[0] + 0x2c) = local_a0._4_4_;
      *(undefined4 *)(local_1f8[0] + 6) = (undefined4)uStack_98;
      *(undefined4 *)((longlong)local_1f8[0] + 0x34) = uStack_98._4_4_;
      local_90 = 0;
      uStack_88 = 0xf;
      local_a0 = local_a0 & 0xffffffffffffff00;
      local_1e8 = FUN_18021478f;
      local_1e0 = &LAB_18021477c;
      local_f0 = (int *)param_1[0x79];
      if (local_f0 != (int *)0x0) {
        LOCK();
        *local_f0 = *local_f0 + 1;
        UNLOCK();
      }
      FUN_18021478f(0,local_1f8,local_e8);
      pcVar2 = local_1e8;
      local_d8 = local_1e8;
      uStack_d0 = local_1e0;
      local_1e8 = _guard_check_icall;
      local_1e0 = (undefined1 *)0x0;
      puVar10 = (undefined8 *)FUN_180e395c0(0x28);
      piVar3 = local_f0;
      local_f0 = (int *)0x0;
      *puVar10 = piVar3;
      (*pcVar2)(0,local_e8,puVar10 + 1);
      *(undefined4 *)(puVar10 + 3) = (undefined4)local_d8;
      *(undefined4 *)((longlong)puVar10 + 0x1c) = local_d8._4_4_;
      *(undefined4 *)(puVar10 + 4) = (undefined4)uStack_d0;
      *(undefined4 *)((longlong)puVar10 + 0x24) = uStack_d0._4_4_;
      local_d8 = _guard_check_icall;
      uStack_d0 = (undefined1 *)0x0;
      local_1c8 = FUN_18007ad0b;
      local_1c0 = FUN_18007acce;
      local_1d8[0] = puVar10;
      if (local_f0 != (int *)0x0) {
        LOCK();
        *local_f0 = *local_f0 + -1;
        UNLOCK();
        if (*local_f0 == 0) {
          thunk_FUN_180e40c7c();
        }
      }
      (*local_1e8)(1,local_1f8,local_1f8);
      (**(code **)(*plVar8 + 0x10))(plVar8,local_1d8,5000000);
      if (0xf < uStack_88) {
        FUN_180073636(local_a0,uStack_88 + 1);
      }
      local_90 = 0;
      uStack_88 = 0xf;
      local_a0 = local_a0 & 0xffffffffffffff00;
      if (0xf < uStack_a8) {
        FUN_180073636(plStack_c0,uStack_a8 + 1);
      }
    }
    if (local_148 != (undefined8 *)0x0) {
      (**(code **)*local_148)(local_148,1);
    }
  }
}

