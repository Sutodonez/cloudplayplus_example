
/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_18021271c(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  longlong param_5)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  longlong lVar4;
  char cVar5;
  undefined8 uVar6;
  undefined1 *puVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined1 auStack_228 [32];
  undefined8 local_208;
  ulonglong **local_200;
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  longlong local_1e0;
  undefined8 local_1d8;
  code *local_1d0;
  undefined1 *local_1c8;
  undefined1 *local_1c0;
  ulonglong *local_1b8;
  undefined8 local_1b0;
  undefined8 uStack_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  undefined8 local_180;
  char *local_178;
  undefined8 local_170;
  char *local_168;
  undefined8 local_160;
  longlong local_158;
  longlong lStack_150;
  undefined8 local_148;
  longlong **local_138;
  undefined4 local_130;
  undefined **local_128;
  longlong local_120;
  undefined ***local_f0;
  longlong *local_e8;
  longlong local_e0;
  undefined1 *local_d8;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined1 local_98 [80];
  ulonglong local_48;
  
  local_48 = DAT_1812df780 ^ (ulonglong)auStack_228;
  if (*(longlong *)(param_1 + 0x730) == param_5) {
    puVar1 = (undefined8 *)(param_1 + 0x9d0);
    plVar8 = *(longlong **)(param_1 + 0x9d0);
    local_e8 = (longlong *)*plVar8;
    local_1f8 = param_2;
    local_1f0 = param_3;
    local_1e8 = param_4;
    if (local_e8 != plVar8) {
      do {
        puVar2 = (undefined8 *)local_e8[4];
        if (puVar2 != (undefined8 *)0x0) {
          (**(code **)*puVar2)(puVar2,1);
        }
        FUN_18007bf72(&local_e8);
      } while (local_e8 != plVar8);
      plVar8 = (longlong *)*puVar1;
    }
    FUN_18011cf6e(puVar1,puVar1,plVar8[1]);
    plVar8[1] = (longlong)plVar8;
    *plVar8 = (longlong)plVar8;
    plVar8[2] = (longlong)plVar8;
    *(undefined8 *)(param_1 + 0x9d8) = 0;
    cVar5 = FUN_18007327e();
    if (cVar5 == '\0') {
      local_e8 = (longlong *)0x18104b8be;
      local_e0 = CONCAT44(local_e0._4_4_,0x7bc9);
      FUN_1800c550c(&DAT_180ff3ee6,&local_e8,"PunchCheckFireWall, punch_epoch: ",param_5);
    }
    local_168 = "119.29.29.29";
    local_160 = 0xc;
    FUN_1800748c4(&local_e8,&local_168,0x35);
    local_178 = "223.5.5.5";
    local_170 = 9;
    FUN_1800748c4(local_98,&local_178,0x35);
    local_1b8 = &local_48;
    local_158 = 0;
    lStack_150 = 0;
    local_148 = 0;
    local_138 = &local_e8;
    FUN_180214304(&local_158,2);
    lVar9 = 0x50;
    do {
      if (0xf < *(ulonglong *)(local_98 + lVar9 + -0x38)) {
        FUN_180073636(*(undefined8 *)(local_98 + lVar9 + -0x50),
                      *(ulonglong *)(local_98 + lVar9 + -0x38) + 1);
      }
      lVar4 = lStack_150;
      *(undefined8 *)(local_98 + lVar9 + -0x40) = 0;
      *(undefined8 *)(local_98 + lVar9 + -0x38) = 0xf;
      local_98[lVar9 + -0x50] = 0;
      lVar9 = lVar9 + -0x50;
    } while (lVar9 != -0x50);
    local_1b8 = (ulonglong *)0xaaaaaaaa00000000;
    local_1b0 = 0;
    uStack_1a8 = 0;
    local_1a0 = 0;
    uStack_198 = 0;
    local_190 = 0;
    uStack_188 = 0;
    local_180 = 0;
    if (local_158 != lStack_150) {
      lVar9 = local_158;
      do {
        local_1c0 = &DAT_aaaaaaaaaaaaaaaa;
        plVar8 = *(longlong **)(param_1 + 0x780);
        uVar6 = FUN_180074b60(local_1f8);
        FUN_180074a38(&local_e8,uVar6,0);
        local_200 = &local_1b8;
        local_208 = local_1e8;
        puVar7 = (undefined1 *)(**(code **)(*plVar8 + 0x18))(plVar8,&local_e8,lVar9,local_1f0);
        if (0xf < CONCAT44(uStack_cc,local_d0)) {
          FUN_180073636(local_e8,CONCAT44(uStack_cc,local_d0) + 1);
        }
        local_1c0 = puVar7;
        if (puVar7 != (undefined1 *)0x0) {
          cVar5 = FUN_18007327e();
          if (cVar5 == '\0') {
            FUN_180074e0e(lVar9,&local_e8);
            local_138 = (longlong **)0x18104b8be;
            local_130 = 0x7c29;
            FUN_1800c550c(&DAT_180ff3b82,&local_138,"firewall check connecting to ",&local_e8);
            if (0xf < CONCAT44(uStack_cc,local_d0)) {
              FUN_180073636(local_e8,CONCAT44(uStack_cc,local_d0) + 1);
            }
          }
          FUN_180219406(puVar1,&local_e8,&local_1c0);
          *(char *)(local_e8 + 5) = '\0';
          puVar7 = local_1c0 + 0xf0;
          lVar3 = *(longlong *)(param_1 + 0x788);
          local_d8 = &LAB_180212ba6;
          local_d0 = 0;
          local_e8 = (longlong *)&LAB_1800aaa18;
          local_e0 = lVar3;
          FUN_180ba3fd0(local_1c0 + 0x100,*(undefined8 *)(local_1c0 + 0x100),&local_e8);
          (**(code **)(lVar3 + 8))(lVar3,puVar7);
          local_128 = &PTR_LAB_18104f290;
          local_120 = param_1;
          local_f0 = &local_128;
          FUN_18018bd9a(local_1c0,param_1);
        }
        lVar9 = lVar9 + 0x50;
      } while (lVar9 != lVar4);
    }
    local_1d8 = *(undefined8 *)(param_1 + 0x730);
    local_1c8 = &LAB_18021972e;
    local_1d0 = FUN_180b76d70;
    local_1e0 = param_1;
    (**(code **)(**(longlong **)(param_1 + 0xa20) + 0x10))
              (*(longlong **)(param_1 + 0xa20),&local_1e0,*(longlong *)(param_1 + 0xa00) * 1000);
    FUN_180a2b820(&uStack_198);
    FUN_180a2b820(&local_1b0);
    FUN_1802143e6(&local_158);
  }
}

