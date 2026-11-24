
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180b27c10(undefined8 *param_1,longlong *param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  char *pcVar8;
  longlong *plVar9;
  undefined8 *puVar10;
  char *_Buf2;
  undefined8 *puVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  size_t sVar15;
  undefined1 auStack_118 [32];
  undefined8 *local_f8;
  char *local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  ulonglong local_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  ulonglong local_b8;
  undefined1 local_a8 [32];
  undefined1 local_88 [32];
  undefined1 local_68 [32];
  ulonglong local_48;
  
  local_48 = DAT_1812df780 ^ (ulonglong)auStack_118;
  local_f8 = param_1;
  lVar5 = (**(code **)(*param_2 + 0x48))(param_2);
  if (*(longlong *)(lVar5 + 8) == 0) {
    local_d0 = (char *)CONCAT44(local_d0._4_4_,0x7d1);
    uVar6 = FUN_180d19220();
    *param_1 = local_d0;
    param_1[1] = uVar6;
  }
  uVar13 = 0;
  local_e0 = 0;
  local_d8 = 0;
  local_f0 = (char *)0x0;
  uStack_e8 = 0;
  FUN_180a2d630(&local_f0,"client_id",9);
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x2f,uVar6);
  FUN_180a2beb0(&local_d0);
  if (0xf < local_d8) {
    FUN_180a2c260(&local_f0,local_f0);
  }
  local_e0 = 0;
  local_d8 = 0;
  local_f0 = (char *)0x0;
  uStack_e8 = 0;
  FUN_180a2d630(&local_f0,&DAT_181239dbc,6);
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x33,uVar6);
  FUN_180a2beb0(&local_d0);
  if (0xf < local_d8) {
    FUN_180a2c260(&local_f0,local_f0);
  }
  local_e0 = 0;
  local_d8 = 0;
  local_f0 = (char *)0x0;
  uStack_e8 = 0;
  FUN_180a2d630(&local_f0,"iceServers",10);
  cVar1 = FUN_180a4c330(lVar5,&local_f0);
  if (0xf < local_d8) {
    FUN_180a2c260(&local_f0,local_f0);
  }
  if (cVar1 != '\0') {
    local_c0 = 0;
    local_b8 = 0;
    local_d0 = (char *)0x0;
    uStack_c8 = 0;
    FUN_180a2d630(&local_d0,"iceServers",10);
    puVar7 = (undefined8 *)FUN_180a4c1f0(lVar5,&local_d0);
    puVar7 = (undefined8 *)(**(code **)(*(longlong *)*puVar7 + 0x38))();
    if (0xf < local_b8) {
      FUN_180a2c260(&local_d0,local_d0);
    }
    local_c0 = 0;
    local_b8 = 0xf;
    local_d0 = (char *)((ulonglong)local_d0 & 0xffffffffffffff00);
    puVar10 = (undefined8 *)puVar7[1];
    for (puVar7 = (undefined8 *)*puVar7; puVar7 != puVar10; puVar7 = puVar7 + 2) {
      uVar6 = FUN_180b2ea60(local_a8,*puVar7);
      if (param_1[0x3c] == param_1[0x3d]) {
        FUN_180b2fe60(param_1 + 0x3b,param_1[0x3c],uVar6);
      }
      else {
        FUN_180ae30c0();
        param_1[0x3c] = param_1[0x3c] + 0x60;
      }
      FUN_180a2beb0(local_68);
      FUN_180a2beb0(local_88);
      FUN_180a2beb0(local_a8);
    }
  }
  local_e0 = 8;
  local_f0 = (char *)0x617461645f707061;
  uStack_e8 = 0;
  local_d8 = 0xf;
  uVar6 = FUN_180b2eb30(&local_d0,param_2,&local_f0);
  FUN_180a39220(param_1 + 0x3e,uVar6);
  if (uStack_c8 != 0) {
    FUN_180a25590();
  }
  local_e0 = 0xd;
  local_d8 = 0xf;
  local_f0 = (char *)0x72656d6165727473;
  uStack_e8 = 0x617461645f;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x40,uVar6);
  FUN_180a2beb0(&local_d0);
  uStack_e8 = 0x64695f6c6f72;
  local_e0 = 0xe;
  local_d8 = 0xf;
  local_f0 = (char *)0x746e6f635f707061;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x44,uVar6);
  FUN_180a2beb0(&local_d0);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x13;
  builtin_strncpy(pcVar8,"controller_platform",0x14);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)(param_1 + 0x2e) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  local_e0 = 0xb;
  local_d8 = 0xf;
  local_f0 = (char *)0x65725f6563726f66;
  uStack_e8 = 0x79616c;
  uVar2 = FUN_180b2ec20(param_2,&local_f0);
  *(undefined1 *)(param_1 + 2) = uVar2;
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x1a;
  local_d8 = 0x1f;
  builtin_strncpy(pcVar8,"force_auto_switch_pkt_loss",0x1b);
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)((longlong)param_1 + 0x14) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x19;
  builtin_strncpy(pcVar8,"force_auto_switch_latency",0x1a);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)(param_1 + 3) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x1d;
  builtin_strncpy(pcVar8,"possible_auto_switch_pkt_loss",0x1e);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)((longlong)param_1 + 0x1c) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x1c;
  builtin_strncpy(pcVar8,"possible_auto_switch_latency",0x1d);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)(param_1 + 4) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x30);
  local_e0 = 0x20;
  builtin_strncpy(pcVar8,"possible_auto_switch_min_latency",0x21);
  local_d8 = 0x2f;
  local_f0 = pcVar8;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)((longlong)param_1 + 0x24) = uVar3;
  FUN_180a2c260(&local_f0,pcVar8,0x2f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x13;
  builtin_strncpy(pcVar8,"auto_switch_network",0x14);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar2 = FUN_180b2ec20(param_2,&local_f0);
  *(undefined1 *)((longlong)param_1 + 0x11) = uVar2;
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0x657079745f73;
  local_e0 = 0xe;
  local_d8 = 0xf;
  local_f0 = (char *)0x6e695f79616c6572;
  uVar3 = FUN_180b2e770(param_2,&local_f0);
  *(undefined4 *)(param_1 + 5) = uVar3;
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x11;
  builtin_strncpy(pcVar8,"publisher_country",0x12);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 6,uVar6);
  FUN_180a2beb0(&local_d0);
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x12;
  builtin_strncpy(pcVar8,"publisher_province",0x13);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 10,uVar6);
  FUN_180a2beb0(&local_d0);
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0x797469635f72;
  local_e0 = 0xe;
  local_d8 = 0xf;
  local_f0 = (char *)0x656873696c627570;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0xe,uVar6);
  FUN_180a2beb0(&local_d0);
  local_e0 = 0xd;
  local_d8 = 0xf;
  local_f0 = (char *)0x656873696c627570;
  uStack_e8 = 0x7073695f72;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x12,uVar6);
  FUN_180a2beb0(&local_d0);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x13;
  builtin_strncpy(pcVar8,"publisher_relay_isp",0x14);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x16,uVar6);
  FUN_180a2beb0(&local_d0);
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_e8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_e0 = 0x12;
  builtin_strncpy(pcVar8,"subscriber_country",0x13);
  local_d8 = 0x1f;
  local_f0 = pcVar8;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x1a,uVar6);
  FUN_180a2beb0(&local_d0);
  FUN_180a2c260(&local_f0,pcVar8,0x1f);
  uStack_c8 = 0;
  pcVar8 = (char *)FUN_180a2e590(0x20);
  local_c0 = 0x13;
  builtin_strncpy(pcVar8,"subscriber_province",0x14);
  local_b8 = 0x1f;
  local_d0 = pcVar8;
  uVar6 = FUN_180b2e690(&local_f0,param_2,&local_d0);
  FUN_180a2b230(param_1 + 0x1e,uVar6);
  if (0xf < local_d8) {
    if (0xfff < local_d8 + 1) {
      if ((char *)0x1f < local_f0 + (-8 - *(longlong *)(local_f0 + -8))) {
                    /* WARNING: Subroutine does not return */
        FUN_180e409dc(*(longlong *)(local_f0 + -8),local_d8 + 0x28);
      }
    }
    thunk_FUN_180e40c7c();
  }
  local_e0 = 0;
  local_d8 = 0xf;
  local_f0 = (char *)((ulonglong)local_f0 & 0xffffffffffffff00);
  thunk_FUN_180e40c7c(pcVar8,0x20);
  local_e0 = 0xf;
  local_d8 = 0xf;
  local_f0 = (char *)0x6269726373627573;
  uStack_e8 = 0x797469635f7265;
  plVar9 = (longlong *)(**(code **)(*param_2 + 0x50))(param_2);
  puVar7 = (undefined8 *)*plVar9;
  puVar10 = (undefined8 *)puVar7[1];
  local_d0 = (char *)puVar7;
  if (*(char *)((longlong)puVar10 + 0x19) == '\0') {
    do {
      puVar11 = puVar10 + 4;
      uVar12 = puVar10[6];
      if (0xf < (ulonglong)puVar10[7]) {
        puVar11 = (undefined8 *)*puVar11;
      }
      uVar14 = uVar12;
      if (0xf < uVar12) {
        uVar14 = 0xf;
      }
      iVar4 = memcmp(puVar11,&local_f0,uVar14);
      if (iVar4 == 0) {
        if (uVar12 < 0xf) {
          cVar1 = -1;
          goto LAB_180b2875c;
        }
        if (0xf < uVar12) goto LAB_180b2875a;
LAB_180b28766:
        puVar11 = (undefined8 *)*puVar10;
        puVar7 = puVar10;
      }
      else {
        if (iVar4 < 0) {
          cVar1 = -1;
        }
        else {
LAB_180b2875a:
          cVar1 = '\x01';
        }
LAB_180b2875c:
        if (-1 < cVar1) goto LAB_180b28766;
        puVar11 = (undefined8 *)puVar10[2];
      }
      puVar10 = puVar11;
    } while (*(char *)((longlong)puVar11 + 0x19) == '\0');
    param_1 = local_f8;
  }
  puVar10 = (undefined8 *)local_d0;
  if (*(char *)((longlong)puVar7 + 0x19) == '\0') {
    puVar11 = puVar7 + 4;
    uVar12 = puVar7[6];
    if (0xf < (ulonglong)puVar7[7]) {
      puVar11 = (undefined8 *)*puVar11;
    }
    sVar15 = 0xf;
    if (uVar12 < 0xf) {
      sVar15 = uVar12;
    }
    iVar4 = memcmp(&local_f0,puVar11,sVar15);
    if (iVar4 == 0) {
      if (0xf < uVar12) {
        cVar1 = -1;
        goto LAB_180b287c2;
      }
      if (uVar12 < 0xf) goto LAB_180b287c0;
    }
    else {
      if (iVar4 < 0) {
        cVar1 = -1;
      }
      else {
LAB_180b287c0:
        cVar1 = '\x01';
      }
LAB_180b287c2:
      if (cVar1 < '\0') goto LAB_180b287c6;
    }
  }
  else {
LAB_180b287c6:
    puVar7 = puVar10;
  }
  puVar10 = (undefined8 *)(**(code **)(*param_2 + 0x50))(param_2);
  if (puVar7 == (undefined8 *)*puVar10) {
    local_e0 = 0;
    uStack_e8 = 0;
    local_f0 = (char *)0x0;
    local_d8 = 0xf;
  }
  else {
    uVar6 = (**(code **)(*(longlong *)puVar7[8] + 0x28))();
    FUN_180a2b330(&local_f0,uVar6);
  }
  FUN_180a2b230(param_1 + 0x22,&local_f0);
  if (0xf < local_d8) {
    uVar12 = local_d8 + 1;
    pcVar8 = local_f0;
    if (0xfff < uVar12) {
      pcVar8 = *(char **)(local_f0 + -8);
      uVar12 = local_d8 + 0x28;
      if ((char *)0x1f < local_f0 + (-8 - (longlong)pcVar8)) goto LAB_180b28cf7;
    }
    thunk_FUN_180e40c7c(pcVar8,uVar12);
  }
  uStack_e8 = 0x7073695f7265;
  local_e0 = 0xe;
  local_d8 = 0xf;
  local_f0 = (char *)0x6269726373627573;
  puVar7 = (undefined8 *)(**(code **)(*param_2 + 0x50))(param_2);
  puVar7 = (undefined8 *)*puVar7;
  puVar10 = (undefined8 *)puVar7[1];
  local_d0 = (char *)puVar7;
  if (*(char *)((longlong)puVar7[1] + 0x19) == '\0') {
    do {
      puVar11 = puVar10 + 4;
      uVar12 = puVar10[6];
      if (0xf < (ulonglong)puVar10[7]) {
        puVar11 = (undefined8 *)*puVar11;
      }
      uVar14 = uVar12;
      if (0xe < uVar12) {
        uVar14 = 0xe;
      }
      iVar4 = memcmp(puVar11,&local_f0,uVar14);
      if (iVar4 == 0) {
        if (uVar12 < 0xe) {
          cVar1 = -1;
          goto LAB_180b288ed;
        }
        if (0xe < uVar12) goto LAB_180b288eb;
LAB_180b288f7:
        puVar11 = (undefined8 *)*puVar10;
        puVar7 = puVar10;
      }
      else {
        if (iVar4 < 0) {
          cVar1 = -1;
        }
        else {
LAB_180b288eb:
          cVar1 = '\x01';
        }
LAB_180b288ed:
        if (-1 < cVar1) goto LAB_180b288f7;
        puVar11 = (undefined8 *)puVar10[2];
      }
      puVar10 = puVar11;
    } while (*(char *)((longlong)puVar11 + 0x19) == '\0');
  }
  puVar10 = (undefined8 *)local_d0;
  if (*(char *)((longlong)puVar7 + 0x19) == '\0') {
    puVar11 = puVar7 + 4;
    uVar12 = puVar7[6];
    if (0xf < (ulonglong)puVar7[7]) {
      puVar11 = (undefined8 *)*puVar11;
    }
    sVar15 = 0xe;
    if (uVar12 < 0xe) {
      sVar15 = uVar12;
    }
    iVar4 = memcmp(&local_f0,puVar11,sVar15);
    if (iVar4 == 0) {
      if (0xe < uVar12) {
        cVar1 = -1;
        goto LAB_180b2894b;
      }
      if (uVar12 < 0xe) goto LAB_180b28949;
    }
    else {
      if (iVar4 < 0) {
        cVar1 = -1;
      }
      else {
LAB_180b28949:
        cVar1 = '\x01';
      }
LAB_180b2894b:
      if (cVar1 < '\0') goto LAB_180b2894f;
    }
  }
  else {
LAB_180b2894f:
    puVar7 = puVar10;
  }
  puVar10 = (undefined8 *)(**(code **)(*param_2 + 0x50))(param_2);
  if (puVar7 == (undefined8 *)*puVar10) {
    local_e0 = 0;
    uStack_e8 = 0;
    local_f0 = (char *)0x0;
    local_d8 = 0xf;
  }
  else {
    uVar6 = (**(code **)(*(longlong *)puVar7[8] + 0x28))();
    FUN_180a2b330(&local_f0,uVar6);
  }
  FUN_180a2b230(param_1 + 0x26,&local_f0);
  if (0xf < local_d8) {
    uVar12 = local_d8 + 1;
    pcVar8 = local_f0;
    if (0xfff < uVar12) {
      pcVar8 = *(char **)(local_f0 + -8);
      uVar12 = local_d8 + 0x28;
      if ((char *)0x1f < local_f0 + (-8 - (longlong)pcVar8)) goto LAB_180b28cf7;
    }
    thunk_FUN_180e40c7c(pcVar8,uVar12);
  }
  uStack_e8 = 0;
  _Buf2 = (char *)FUN_180a2e590(0x20);
  local_d8 = 0x1f;
  builtin_strncpy(_Buf2,"subscriber_relay_isp",0x15);
  local_e0 = 0x14;
  local_f0 = _Buf2;
  puVar7 = (undefined8 *)(**(code **)(*param_2 + 0x50))(param_2);
  puVar7 = (undefined8 *)*puVar7;
  local_d0 = (char *)puVar7;
  if (*(char *)((longlong)puVar7[1] + 0x19) == '\0') {
    puVar10 = (undefined8 *)puVar7[1];
    do {
      puVar11 = puVar10 + 4;
      uVar12 = puVar10[6];
      if (0xf < (ulonglong)puVar10[7]) {
        puVar11 = (undefined8 *)*puVar11;
      }
      uVar14 = uVar12;
      if (0x14 < uVar12) {
        uVar14 = 0x14;
      }
      iVar4 = memcmp(puVar11,_Buf2,uVar14);
      if (iVar4 == 0) {
        if (uVar12 < 0x14) {
          cVar1 = -1;
          goto LAB_180b28a8b;
        }
        if (0x14 < uVar12) goto LAB_180b28a89;
LAB_180b28a95:
        puVar11 = (undefined8 *)*puVar10;
        puVar7 = puVar10;
      }
      else {
        if (iVar4 < 0) {
          cVar1 = -1;
        }
        else {
LAB_180b28a89:
          cVar1 = '\x01';
        }
LAB_180b28a8b:
        if (-1 < cVar1) goto LAB_180b28a95;
        puVar11 = (undefined8 *)puVar10[2];
      }
      puVar10 = puVar11;
    } while (*(char *)((longlong)puVar11 + 0x19) == '\0');
    param_1 = local_f8;
  }
  if (*(char *)((longlong)puVar7 + 0x19) == '\0') {
    puVar10 = puVar7 + 4;
    uVar12 = puVar7[6];
    if (0xf < (ulonglong)puVar7[7]) {
      puVar10 = (undefined8 *)*puVar10;
    }
    sVar15 = 0x14;
    if (uVar12 < 0x14) {
      sVar15 = uVar12;
    }
    iVar4 = memcmp(_Buf2,puVar10,sVar15);
    if (iVar4 == 0) {
      if (0x14 < uVar12) {
        cVar1 = -1;
        goto LAB_180b28af2;
      }
      if (uVar12 < 0x14) goto LAB_180b28af0;
    }
    else {
      if (iVar4 < 0) {
        cVar1 = -1;
      }
      else {
LAB_180b28af0:
        cVar1 = '\x01';
      }
LAB_180b28af2:
      if (cVar1 < '\0') goto LAB_180b28af6;
    }
  }
  else {
LAB_180b28af6:
    puVar7 = (undefined8 *)local_d0;
  }
  puVar10 = (undefined8 *)(**(code **)(*param_2 + 0x50))(param_2);
  if (puVar7 == (undefined8 *)*puVar10) {
    local_e0 = 0;
    uStack_e8 = 0;
    local_f0 = (char *)0x0;
    local_d8 = 0xf;
  }
  else {
    uVar6 = (**(code **)(*(longlong *)puVar7[8] + 0x28))();
    FUN_180a2b330(&local_f0,uVar6);
  }
  FUN_180a2b230(param_1 + 0x2a,&local_f0);
  if (0xf < local_d8) {
    if (0xfff < local_d8 + 1) {
      pcVar8 = *(char **)(local_f0 + -8);
      uVar12 = local_d8 + 0x28;
      if ((char *)0x1f < local_f0 + (-8 - (longlong)pcVar8)) {
LAB_180b28cf7:
                    /* WARNING: Subroutine does not return */
        FUN_180e409dc(pcVar8,uVar12);
      }
    }
    thunk_FUN_180e40c7c();
  }
  FUN_180a2c260(&local_f0,_Buf2,0x1f);
  local_d0 = (char *)((ulonglong)local_d0 & 0xffffffff00000000);
  uVar6 = FUN_180d19220();
  uStack_c8._0_4_ = (undefined4)uVar6;
  uStack_c8._4_4_ = (undefined4)((ulonglong)uVar6 >> 0x20);
  local_e0 = 4;
  local_d8 = 0xf;
  uStack_e8 = 0;
  *(undefined4 *)param_1 = (undefined4)local_d0;
  *(undefined4 *)((longlong)param_1 + 4) = local_d0._4_4_;
  *(undefined4 *)(param_1 + 1) = (undefined4)uStack_c8;
  *(undefined4 *)((longlong)param_1 + 0xc) = uStack_c8._4_4_;
  local_f0 = (char *)0x65646f63;
  uStack_c8 = uVar6;
  iVar4 = FUN_180b2e770(param_2,&local_f0);
  if (iVar4 < 0xdbba2) {
    if (iVar4 == 0xdbba1) {
      uVar13 = 0x7d4;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0) goto LAB_180b28c5b;
    if (iVar4 == 0x186a1) {
      uVar13 = 0x7e5;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0x186a2) {
      uVar13 = 0x7e6;
      goto LAB_180b28c5b;
    }
  }
  else {
    if (iVar4 == 0xdbba2) {
      uVar13 = 0x7e7;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0xdbba3) {
      uVar13 = 0x7e8;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0xdbba4) {
      uVar13 = 0x7ea;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0xdbba5) {
      uVar13 = 0x7eb;
      goto LAB_180b28c5b;
    }
    if (iVar4 == 0xdbba6) {
      uVar13 = 0x7ec;
      goto LAB_180b28c5b;
    }
  }
  uVar13 = 0x7e9;
LAB_180b28c5b:
  FUN_180a2e440(param_1,uVar13);
  local_e0 = 3;
  uStack_e8 = 0;
  local_d8 = 0xf;
  local_f0 = (char *)0x67736d;
  uVar6 = FUN_180b2e690(&local_d0,param_2,&local_f0);
  FUN_180a2b230(param_1 + 0x37,uVar6);
  FUN_180a2beb0(&local_d0);
}

