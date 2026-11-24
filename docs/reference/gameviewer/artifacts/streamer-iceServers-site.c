
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180b271b0(undefined8 *param_1,longlong *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  longlong *plVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  char *pcVar11;
  undefined8 *puVar12;
  ulonglong uVar13;
  undefined8 *puVar14;
  longlong *plVar15;
  ulonglong uVar16;
  size_t _Size;
  undefined1 auStack_198 [32];
  longlong local_178;
  longlong lStack_170;
  longlong local_168;
  longlong *local_160;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 local_140;
  ulonglong local_138;
  undefined1 local_128 [32];
  undefined1 local_108 [32];
  undefined1 local_e8 [32];
  undefined1 local_c8 [32];
  undefined1 local_a8 [48];
  undefined1 local_78 [32];
  ulonglong local_58;
  
  local_58 = DAT_1812df780 ^ (ulonglong)auStack_198;
  local_160 = param_2;
  plVar7 = (longlong *)(**(code **)(*param_2 + 0x48))(param_2);
  if (plVar7[1] == 0) {
    local_160 = (longlong *)CONCAT44(local_160._4_4_,0x7d1);
    uVar8 = FUN_180d19220();
    *param_1 = local_160;
    param_1[1] = uVar8;
  }
  uStack_148 = 0;
  local_140 = 7;
  local_138 = 0xf;
  local_150 = (char *)0x64695f6d6f6f72;
  uVar8 = FUN_180b2e690(local_78,param_2,&local_150);
  FUN_180a2b230(param_1 + 3,uVar8);
  FUN_180a2beb0(local_78);
  local_150 = (char *)0x656873696c627570;
  uStack_148 = 0x72;
  local_178 = 0;
  lStack_170 = 0;
  local_168 = 0;
  local_140 = 9;
  local_138 = 0xf;
  cVar4 = FUN_180a4c330(plVar7,&local_150);
  if (cVar4 != '\0') {
    local_140 = 9;
    local_150 = (char *)0x656873696c627570;
    uStack_148 = 0x72;
    local_138 = 0xf;
    puVar9 = (undefined8 *)FUN_180a4c1f0(plVar7,&local_150);
    uVar8 = FUN_180b2e830(local_128,*puVar9);
    FUN_180a44480(param_1 + 7,uVar8);
    FUN_180a2b820(local_a8);
    FUN_180a2beb0(local_c8);
    FUN_180a2beb0(local_e8);
    FUN_180a2beb0(local_108);
    FUN_180a2beb0(local_128);
    FUN_180a2beb0(&local_150);
  }
  puVar9 = (undefined8 *)*plVar7;
  uStack_148 = 0;
  local_140 = 3;
  local_138 = 0xf;
  local_150 = (char *)0x756f79;
  if (*(char *)((longlong)puVar9[1] + 0x19) == '\0') {
    puVar14 = (undefined8 *)puVar9[1];
    do {
      puVar12 = puVar14 + 4;
      uVar13 = puVar14[6];
      if (0xf < (ulonglong)puVar14[7]) {
        puVar12 = (undefined8 *)*puVar12;
      }
      uVar16 = uVar13;
      if (3 < uVar13) {
        uVar16 = 3;
      }
      iVar5 = memcmp(puVar12,&local_150,uVar16);
      if (iVar5 == 0) {
        if (uVar13 < 3) {
          cVar4 = -1;
          goto LAB_180b2740d;
        }
        if (3 < uVar13) goto LAB_180b2740b;
LAB_180b27417:
        puVar12 = (undefined8 *)*puVar14;
        puVar9 = puVar14;
      }
      else {
        if (iVar5 < 0) {
          cVar4 = -1;
        }
        else {
LAB_180b2740b:
          cVar4 = '\x01';
        }
LAB_180b2740d:
        if (-1 < cVar4) goto LAB_180b27417;
        puVar12 = (undefined8 *)puVar14[2];
      }
      puVar14 = puVar12;
    } while (*(char *)((longlong)puVar12 + 0x19) == '\0');
  }
  if (*(char *)((longlong)puVar9 + 0x19) == '\0') {
    plVar15 = puVar9 + 4;
    if (0xf < (ulonglong)puVar9[7]) {
      plVar15 = (longlong *)*plVar15;
    }
    iVar5 = FUN_180a3fdf0(&local_150,3,plVar15,puVar9[6]);
    if (iVar5 != 0) {
      cVar4 = -1;
      if (-1 < iVar5) {
        cVar4 = '\x01';
      }
      if (cVar4 < '\0') goto LAB_180b2746d;
    }
    bVar3 = true;
  }
  else {
LAB_180b2746d:
    bVar3 = false;
  }
  if (bVar3) {
    local_140 = 3;
    uStack_148 = 0;
    local_150 = (char *)0x756f79;
    local_138 = 0xf;
    puVar9 = (undefined8 *)FUN_180a4c1f0(plVar7,&local_150);
    uVar8 = FUN_180b2e830(local_128,*puVar9);
    FUN_180a44480(param_1 + 0x1c,uVar8);
    FUN_180a2b820(local_a8);
    FUN_180a2beb0(local_c8);
    FUN_180a2beb0(local_e8);
    FUN_180a2beb0(local_108);
    FUN_180a2beb0(local_128);
    if (0xf < local_138) {
      FUN_180a2c260(&local_150,local_150);
    }
  }
  local_150 = (char *)0x6269726373627573;
  uStack_148 = 0x737265;
  local_140 = 0xb;
  local_138 = 0xf;
  cVar4 = FUN_180a4c330(plVar7,&local_150);
  if (cVar4 != '\0') {
    local_140 = 0xb;
    local_138 = 0xf;
    local_150 = (char *)0x6269726373627573;
    uStack_148 = 0x737265;
    puVar9 = (undefined8 *)FUN_180a4c1f0(plVar7,&local_150);
    puVar9 = (undefined8 *)(**(code **)(*(longlong *)*puVar9 + 0x38))();
    if (0xf < local_138) {
      FUN_180a2c260(&local_150,local_150);
    }
    local_140 = 0;
    local_138 = 0xf;
    local_150 = (char *)((ulonglong)local_150 & 0xffffffffffffff00);
    puVar14 = (undefined8 *)puVar9[1];
    for (puVar9 = (undefined8 *)*puVar9; puVar9 != puVar14; puVar9 = puVar9 + 2) {
      uVar8 = FUN_180b2e830(local_128,*puVar9);
      if (lStack_170 == local_168) {
        FUN_180b2fca0(&local_178,lStack_170,uVar8);
      }
      else {
        FUN_180a467f0(lStack_170,uVar8);
        lStack_170 = lStack_170 + 0xa8;
      }
      FUN_180a2b820(local_a8);
      FUN_180a2beb0(local_c8);
      FUN_180a2beb0(local_e8);
      FUN_180a2beb0(local_108);
      FUN_180a2beb0(local_128);
    }
  }
  local_140 = 10;
  local_138 = 0xf;
  local_150 = (char *)0x6576726553656369;
  puVar9 = (undefined8 *)((undefined8 *)*plVar7)[1];
  uStack_148 = 0x7372;
  cVar4 = *(char *)((longlong)puVar9 + 0x19);
  puVar14 = (undefined8 *)*plVar7;
  while (cVar4 == '\0') {
    puVar12 = puVar9 + 4;
    uVar13 = puVar9[6];
    if (0xf < (ulonglong)puVar9[7]) {
      puVar12 = (undefined8 *)*puVar12;
    }
    uVar16 = uVar13;
    if (10 < uVar13) {
      uVar16 = 10;
    }
    iVar5 = memcmp(puVar12,&local_150,uVar16);
    if (iVar5 == 0) {
      if (uVar13 < 10) {
        cVar4 = -1;
        goto LAB_180b276dd;
      }
      if (10 < uVar13) goto LAB_180b276db;
LAB_180b276e7:
      puVar12 = (undefined8 *)*puVar9;
    }
    else {
      if (iVar5 < 0) {
        cVar4 = -1;
      }
      else {
LAB_180b276db:
        cVar4 = '\x01';
      }
LAB_180b276dd:
      if (-1 < cVar4) goto LAB_180b276e7;
      puVar12 = (undefined8 *)puVar9[2];
      puVar9 = puVar14;
    }
    puVar14 = puVar9;
    puVar9 = puVar12;
    cVar4 = *(char *)((longlong)puVar12 + 0x19);
  }
  if (*(char *)((longlong)puVar14 + 0x19) == '\0') {
    puVar9 = puVar14 + 4;
    uVar13 = puVar14[6];
    if (0xf < (ulonglong)puVar14[7]) {
      puVar9 = (undefined8 *)*puVar9;
    }
    _Size = 10;
    if (uVar13 < 10) {
      _Size = uVar13;
    }
    iVar5 = memcmp(&local_150,puVar9,_Size);
    if (iVar5 == 0) {
      if (10 < uVar13) {
        cVar4 = -1;
        goto LAB_180b27736;
      }
      if (uVar13 < 10) goto LAB_180b27734;
    }
    else {
      if (iVar5 < 0) {
        cVar4 = -1;
      }
      else {
LAB_180b27734:
        cVar4 = '\x01';
      }
LAB_180b27736:
      if (cVar4 < '\0') goto LAB_180b2773e;
    }
    bVar3 = true;
  }
  else {
LAB_180b2773e:
    bVar3 = false;
  }
  if (bVar3) {
    local_140 = 10;
    local_150 = (char *)0x6576726553656369;
    uStack_148 = 0x7372;
    local_138 = 0xf;
    puVar9 = (undefined8 *)FUN_180a4c1f0(plVar7,&local_150);
    puVar9 = (undefined8 *)(**(code **)(*(longlong *)*puVar9 + 0x38))();
    if (0xf < local_138) {
      if (0xfff < local_138 + 1) {
        if (0x1f < ((longlong)local_150 - *(longlong *)((longlong)local_150 - 8)) - 8U) {
                    /* WARNING: Subroutine does not return */
          FUN_180e409dc(*(longlong *)((longlong)local_150 - 8),local_138 + 0x28);
        }
      }
      thunk_FUN_180e40c7c();
    }
    local_138 = 0xf;
    local_140 = 0;
    local_150 = (char *)((ulonglong)local_150 & 0xffffffffffffff00);
    puVar14 = (undefined8 *)puVar9[1];
    for (puVar9 = (undefined8 *)*puVar9; puVar9 != puVar14; puVar9 = puVar9 + 2) {
      puVar10 = (undefined8 *)FUN_180b2ea60(local_128,*puVar9);
      puVar12 = (undefined8 *)param_1[0x35];
      if (puVar12 == (undefined8 *)param_1[0x36]) {
        FUN_180b2fe60(param_1 + 0x34,puVar12,puVar10);
      }
      else {
        *puVar12 = 0;
        puVar12[1] = 0;
        puVar12[2] = 0;
        puVar12[3] = 0;
        uVar8 = puVar10[1];
        *puVar12 = *puVar10;
        puVar12[1] = uVar8;
        uVar8 = puVar10[3];
        puVar12[2] = puVar10[2];
        puVar12[3] = uVar8;
        puVar10[3] = 0xf;
        puVar10[2] = 0;
        *(undefined1 *)puVar10 = 0;
        puVar12[4] = 0;
        puVar12[5] = 0;
        puVar12[6] = 0;
        puVar12[7] = 0;
        uVar8 = puVar10[5];
        puVar12[4] = puVar10[4];
        puVar12[5] = uVar8;
        uVar8 = puVar10[7];
        puVar12[6] = puVar10[6];
        puVar12[7] = uVar8;
        puVar10[7] = 0xf;
        puVar10[6] = 0;
        *(undefined1 *)(puVar10 + 4) = 0;
        puVar12[8] = 0;
        puVar12[9] = 0;
        puVar12[10] = 0;
        puVar12[0xb] = 0;
        uVar6 = *(undefined4 *)((longlong)puVar10 + 0x44);
        uVar1 = *(undefined4 *)(puVar10 + 9);
        uVar2 = *(undefined4 *)((longlong)puVar10 + 0x4c);
        *(undefined4 *)(puVar12 + 8) = *(undefined4 *)(puVar10 + 8);
        *(undefined4 *)((longlong)puVar12 + 0x44) = uVar6;
        *(undefined4 *)(puVar12 + 9) = uVar1;
        *(undefined4 *)((longlong)puVar12 + 0x4c) = uVar2;
        uVar8 = puVar10[0xb];
        puVar12[10] = puVar10[10];
        puVar12[0xb] = uVar8;
        puVar10[10] = 0;
        puVar10[0xb] = 0xf;
        *(undefined1 *)(puVar10 + 8) = 0;
        param_1[0x35] = param_1[0x35] + 0x60;
      }
      FUN_180a2beb0(local_e8);
      FUN_180a2beb0(local_108);
      FUN_180a2beb0(local_128);
    }
  }
  FUN_180a459f0(param_1 + 0x31,&local_178);
  local_150 = (char *)((ulonglong)local_150 & 0xffffffff00000000);
  uVar8 = FUN_180d19220();
  uStack_148._0_4_ = (undefined4)uVar8;
  uVar6 = (undefined4)uStack_148;
  uStack_148._4_4_ = (undefined4)((ulonglong)uVar8 >> 0x20);
  uVar1 = uStack_148._4_4_;
  uStack_148 = 0;
  *(undefined4 *)param_1 = (undefined4)local_150;
  *(undefined4 *)((longlong)param_1 + 4) = local_150._4_4_;
  *(undefined4 *)(param_1 + 1) = uVar6;
  *(undefined4 *)((longlong)param_1 + 0xc) = uVar1;
  pcVar11 = (char *)FUN_180a2e590(0x20);
  builtin_strncpy(pcVar11,"reconnect_buffer",0x11);
  local_140 = 0x10;
  local_138 = 0x1f;
  local_150 = pcVar11;
  uVar6 = FUN_180b2e770(local_160,&local_150);
  *(undefined4 *)(param_1 + 2) = uVar6;
  thunk_FUN_180e40c7c(pcVar11,0x20);
  if (local_178 != 0) {
    FUN_180a2e470(local_178,lStack_170);
    uVar13 = (local_168 - local_178 >> 3) * 8;
    if (0xfff < uVar13) {
      if (0x1f < (local_178 - *(longlong *)(local_178 + -8)) - 8U) {
                    /* WARNING: Subroutine does not return */
        FUN_180e409dc(*(longlong *)(local_178 + -8),uVar13 + 0x27);
      }
    }
    thunk_FUN_180e40c7c();
  }
}

