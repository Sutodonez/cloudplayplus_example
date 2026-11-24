
longlong * FUN_180d162d0(longlong *param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  longlong *plVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  longlong *plVar13;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar14;
  undefined4 extraout_XMM0_Da_00;
  undefined4 extraout_XMM0_Da_01;
  undefined4 extraout_XMM0_Da_02;
  undefined4 extraout_XMM0_Da_03;
  undefined4 extraout_XMM0_Da_04;
  undefined4 extraout_XMM0_Da_05;
  undefined4 extraout_XMM0_Da_06;
  char *local_48;
  undefined8 local_40;
  char *local_38;
  undefined8 local_30;
  
  lVar12 = param_2[1];
  lVar10 = param_2[2];
  lVar11 = param_2[3];
  *param_1 = *param_2;
  param_1[1] = lVar12;
  lVar12 = param_2[4];
  lVar9 = param_2[5];
  param_1[2] = lVar10;
  param_1[3] = lVar11;
  lVar10 = param_2[6];
  lVar11 = param_2[7];
  param_1[4] = lVar12;
  param_1[5] = lVar9;
  lVar12 = param_2[8];
  lVar9 = param_2[9];
  param_1[6] = lVar10;
  param_1[7] = lVar11;
  lVar10 = param_2[10];
  lVar11 = param_2[0xb];
  param_1[8] = lVar12;
  param_1[9] = lVar9;
  lVar12 = param_2[0xc];
  lVar9 = param_2[0xd];
  param_1[10] = lVar10;
  param_1[0xb] = lVar11;
  lVar10 = param_2[0xe];
  uVar5 = *(undefined4 *)((longlong)param_2 + 0x74);
  lVar11 = param_2[0xf];
  uVar6 = *(undefined4 *)((longlong)param_2 + 0x7c);
  param_1[0xc] = lVar12;
  param_1[0xd] = lVar9;
  uVar14 = (undefined4)param_2[0x10];
  uVar7 = *(undefined4 *)((longlong)param_2 + 0x84);
  lVar12 = param_2[0x11];
  uVar8 = *(undefined4 *)((longlong)param_2 + 0x8c);
  *(int *)(param_1 + 0xe) = (int)lVar10;
  *(undefined4 *)((longlong)param_1 + 0x74) = uVar5;
  *(int *)(param_1 + 0xf) = (int)lVar11;
  *(undefined4 *)((longlong)param_1 + 0x7c) = uVar6;
  *(undefined4 *)(param_1 + 0x10) = uVar14;
  *(undefined4 *)((longlong)param_1 + 0x84) = uVar7;
  *(int *)(param_1 + 0x11) = (int)lVar12;
  *(undefined4 *)((longlong)param_1 + 0x8c) = uVar8;
  if (*param_1 == 0) {
    local_40 = 0x26;
    local_48 = "ControllerCallback.OnReceiveMediaTrack";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_38 = "streamer callback fallback in use: {}";
      local_30 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_38,&local_48);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    *param_1 = (longlong)_guard_check_icall;
  }
  if (param_1[1] == 0) {
    local_30 = 0x25;
    local_38 = "ControllerCallback.OnRemoveMediaTrack";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_00;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[1] = (longlong)_guard_check_icall;
  }
  if (param_1[2] == 0) {
    local_30 = 0x20;
    local_38 = "ControllerCallback.OnFrameChange";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_01;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[2] = (longlong)_guard_check_icall;
  }
  if (param_1[3] == 0) {
    local_30 = 0x27;
    local_38 = "ControllerCallback.OnReceiveControlData";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_02;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[3] = (longlong)_guard_check_icall;
  }
  if (param_1[4] == 0) {
    local_30 = 0x24;
    local_38 = "ControllerCallback.OnReceiveTextData";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_03;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[4] = (longlong)_guard_check_icall;
  }
  if (param_1[5] == 0) {
    local_30 = 0x24;
    local_38 = "ControllerCallback.OnReceiveFileData";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_04;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[5] = (longlong)_guard_check_icall;
  }
  if (param_1[6] == 0) {
    local_30 = 0x26;
    local_38 = "ControllerCallback.OnReceiveBinaryData";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_05;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[6] = (longlong)_guard_check_icall;
  }
  if (param_1[7] == 0) {
    local_30 = 0x1e;
    local_38 = "ControllerCallback.OnRoomState";
    lVar12 = FUN_180d05fb0();
    plVar13 = (longlong *)FUN_180c5cdf0(lVar12 + 0x108);
    plVar4 = *(longlong **)(lVar12 + 0x100);
    if (plVar13 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
      UNLOCK();
    }
    LOCK();
    uVar3 = *(undefined8 *)(lVar12 + 0x108);
    *(undefined8 *)(lVar12 + 0x108) = plVar13;
    UNLOCK();
    uVar14 = extraout_XMM0_Da_06;
    if (((byte)uVar3 & 3) == 2) {
      uVar14 = FUN_180e33f94(lVar12 + 0x108);
    }
    if ((plVar4 == (longlong *)0x0) || (lVar12 = *plVar4, lVar12 == 0)) {
      if (plVar13 != (longlong *)0x0) {
        uVar14 = FUN_180a25590(plVar13);
      }
    }
    else {
      local_48 = "streamer callback fallback in use: {}";
      local_40 = 0x25;
      uVar14 = FUN_180aa7a30(lVar12,3,&local_48,&local_38);
      if (plVar13 != (longlong *)0x0) {
        LOCK();
        plVar4 = plVar13 + 1;
        lVar12 = *plVar4;
        *(int *)plVar4 = (int)*plVar4 + -1;
        UNLOCK();
        if ((int)lVar12 == 1) {
          uVar14 = (**(code **)*plVar13)(plVar13);
          LOCK();
          piVar1 = (int *)((longlong)plVar13 + 0xc);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 == 1) {
            uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
    }
    param_1[7] = (longlong)_guard_check_icall;
  }
  if (param_1[8] == 0) {
    local_30 = 0x1f;
    local_38 = "ControllerCallback.OnSignalPush";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[8] = (longlong)_guard_check_icall;
  }
  if (param_1[9] == 0) {
    local_30 = 0x1d;
    local_38 = "ControllerCallback.OnQosStats";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[9] = (longlong)_guard_check_icall;
  }
  if (param_1[10] == 0) {
    local_30 = 0x1c;
    local_38 = "ControllerCallback.OnNatInfo";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[10] = (longlong)_guard_check_icall;
  }
  if (param_1[0xb] == 0) {
    local_30 = 0x28;
    local_38 = "ControllerCallback.OnPeerConnectionState";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0xb] = (longlong)_guard_check_icall;
  }
  if (param_1[0xc] == 0) {
    local_30 = 0x28;
    local_38 = "ControllerCallback.OnConnectionStateCode";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0xc] = (longlong)_guard_check_icall;
  }
  if (param_1[0xd] == 0) {
    local_30 = 0x20;
    local_38 = "ControllerCallback.OnEventReport";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0xd] = (longlong)_guard_check_icall;
  }
  if (param_1[0xe] == 0) {
    local_30 = 0x2c;
    local_38 = "ControllerCallback.OnDualNegotiateCapability";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0xe] = (longlong)_guard_check_icall;
  }
  if (param_1[0xf] == 0) {
    local_30 = 0x27;
    local_38 = "ControllerCallback.OnReceiveDataChannel";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0xf] = (longlong)_guard_check_icall;
  }
  if (param_1[0x10] == 0) {
    local_30 = 0x1f;
    local_38 = "ControllerCallback.OnSignalData";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    uVar14 = FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0x10] = (longlong)_guard_check_icall;
  }
  if (param_1[0x11] == 0) {
    local_30 = 0x21;
    local_38 = "ControllerCallback.OnSignalHandle";
    local_48 = "streamer callback fallback in use: {}";
    local_40 = 0x25;
    FUN_180aeefc0(uVar14,&local_48,&local_38);
    param_1[0x11] = (longlong)_guard_check_icall;
  }
  return param_1;
}

