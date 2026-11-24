
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_14070d3d0(longlong param_1,HANDLE param_2,LPVOID param_3,uint param_4,LPCWSTR param_5,
             undefined8 *param_6,undefined4 param_7,undefined4 param_8,longlong param_9,
             undefined8 param_10,undefined8 param_11)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  char *pcVar14;
  char cVar15;
  char cVar16;
  uint uVar17;
  BOOL BVar18;
  DWORD DVar19;
  char *pcVar20;
  undefined2 *puVar21;
  longlong lVar22;
  ulonglong uVar23;
  undefined8 uVar24;
  longlong *plVar25;
  undefined8 *puVar26;
  LPWSTR ******pppppppWVar27;
  HANDLE pvVar28;
  ulonglong *puVar29;
  ulonglong uVar30;
  LPCWSTR lpApplicationName;
  HANDLE hThread;
  ulonglong uVar31;
  undefined8 *******_Src;
  uint uVar32;
  longlong lVar33;
  bool bVar34;
  bool bVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  undefined1 auStackY_588 [32];
  uint uStack_524;
  undefined2 auStack_520 [4];
  undefined8 uStack_518;
  undefined8 uStack_510;
  char *pcStack_508;
  char *pcStack_500;
  char *pcStack_4f8;
  char *pcStack_4f0;
  undefined8 uStack_4e8;
  longlong lStack_4e0;
  char *pcStack_4d8;
  undefined8 uStack_4d0;
  longlong *plStack_4c8;
  HANDLE pvStack_4c0;
  ulonglong uStack_4b8;
  HANDLE pvStack_4b0;
  undefined8 uStack_4a8;
  char *pcStack_498;
  size_t sStack_490;
  uint uStack_488;
  undefined4 uStack_480;
  undefined4 uStack_478;
  uint uStack_470;
  HANDLE pvStack_468;
  undefined1 auStack_458 [32];
  undefined1 auStack_438 [24];
  char cStack_420;
  HANDLE pvStack_418;
  undefined8 uStack_410;
  char *pcStack_408;
  LPCWSTR pWStack_3f8;
  undefined8 *puStack_3f0;
  longlong lStack_3e8;
  undefined1 auStack_3e0 [32];
  char cStack_3c0;
  LPVOID pvStack_3b8;
  longlong lStack_3b0;
  HANDLE pvStack_3a8;
  undefined8 *puStack_3a0;
  _PROCESS_INFORMATION _Stack_398;
  undefined8 *puStack_378;
  undefined8 uStack_370;
  char *pcStack_368;
  undefined8 uStack_360;
  char *pcStack_358;
  undefined8 uStack_350;
  char *pcStack_348;
  undefined8 uStack_340;
  char *pcStack_338;
  undefined8 uStack_330;
  char *pcStack_308;
  undefined8 uStack_300;
  char *pcStack_2f8;
  undefined8 uStack_2f0;
  undefined1 auStack_2e8 [8];
  undefined1 auStack_2e0 [8];
  undefined1 auStack_2d8 [16];
  _STARTUPINFOW _Stack_2c8;
  undefined1 auStack_258 [272];
  LPWSTR ******pppppppWStack_148;
  LPWSTR *****ppppppWStack_140;
  LPWSTR *****ppppppWStack_138;
  LPWSTR *****ppppppWStack_130;
  undefined8 *******pppppppuStack_128;
  undefined8 uStack_120;
  ulonglong uStack_118;
  ulonglong uStack_110;
  char acStack_108 [8];
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  ulonglong uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  ulonglong uStack_c8;
  longlong alStack_c0 [2];
  longlong lStack_b0;
  ulonglong uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  longlong lStack_90;
  undefined8 uStack_88;
  char cStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  ulonglong uStack_58;
  
  uStack_58 = DAT_141e01000 ^ (ulonglong)auStackY_588;
  pWStack_3f8 = param_5;
  puStack_3f0 = param_6;
  uStack_480 = param_7;
  uStack_478 = param_8;
  uStack_510 = param_10;
  uStack_518 = param_11;
  lVar33 = 0;
  uStack_524 = 0;
  lStack_4e0 = param_1;
  uStack_488 = param_4;
  uStack_470 = param_4;
  pvStack_468 = param_2;
  pcStack_408 = param_3;
  lStack_3e8 = param_1;
  pvStack_3b8 = param_3;
  pvStack_3a8 = param_2;
  cVar15 = FUN_1407003e0(param_9,param_10);
  if (cVar15 == '\0') {
    return 0;
  }
  puVar26 = (undefined8 *)(param_1 + 0x100);
  puStack_3a0 = puVar26;
  cVar15 = thunk_FUN_1406faf10(puVar26,0);
  pvVar28 = pvStack_468;
  if ((((cVar15 != '\0') || (*(longlong *)(param_1 + 0x2c8) == 0)) ||
      (*(longlong *)(param_1 + 0x2e8) == 0)) || (*(longlong *)(param_1 + 0x308) == 0)) {
LAB_14070d521:
    thunk_FUN_14016cb60(param_11,"visible_terminal_unavailable",0x1c);
    return 0;
  }
  cVar15 = thunk_FUN_14071c910(*puVar26,pvStack_468);
  if (cVar15 == '\0') {
    cVar15 = FUN_1407003e0(param_9,param_10,param_11);
    if (cVar15 == '\0') {
      return 0;
    }
    goto LAB_14070d521;
  }
  FUN_1407017b0(alStack_c0);
  uStack_d8 = 0;
  uStack_d0 = 0;
  uStack_c8 = 7;
  uStack_e0 = 0;
  if (lStack_b0 != 0) {
    pcVar20 = (char *)thunk_FUN_14071c8e0(*puVar26);
    pcStack_498 = pcVar20;
    if (0xf < *(ulonglong *)(pcVar20 + 0x18)) {
      pcStack_498 = *(char **)pcVar20;
    }
    sStack_490 = *(size_t *)(pcVar20 + 0x10);
    cVar15 = thunk_FUN_1402287e0(&pcStack_498,&uStack_e0);
    if (cVar15 != '\0') {
      pcStack_500 = (char *)0x0;
      pcStack_4f8 = (char *)0x0;
      pcStack_4f0 = (char *)0x0;
      thunk_FUN_1407462f0(auStack_3e0,pvVar28);
      if (cStack_3c0 == '\0') {
        auStack_520[0] = 0x100;
        puVar21 = auStack_520;
      }
      else {
        puVar21 = (undefined2 *)thunk_FUN_140c91cd0(auStack_520,auStack_3e0);
      }
      if ((char)((ushort)*puVar21 >> 8) == '\0') {
        cVar15 = thunk_FUN_140202db0(3);
        if (cVar15 != '\0') {
          lVar22 = thunk_FUN_1402088f0(auStack_258,3);
          lVar33 = 1;
          uStack_524 = 1;
          if (*(char *)(lVar22 + 0xf8) != '\0') {
            thunk_FUN_14015d4f0(lVar22 + 0x10,
                                "terminal visible attach result=fallback reason=windows_terminal_config_unavailable fallback=powershell_or_cmd"
                               );
          }
        }
joined_r0x00014070d730:
        if (lVar33 != 0) {
          uStack_524 = 0;
          thunk_FUN_140208c50(auStack_258);
        }
      }
      else {
        if ((char)*puVar21 != '\0') {
          cVar15 = thunk_FUN_140202db0(2);
          if (cVar15 != '\0') {
            lVar22 = thunk_FUN_1402088f0(auStack_258,2);
            lVar33 = 2;
            uStack_524 = 2;
            if (*(char *)(lVar22 + 0xf8) != '\0') {
              thunk_FUN_14015d4f0(lVar22 + 0x10,
                                  "terminal visible attach result=fallback reason=windows_terminal_elevated_profile"
                                 );
            }
          }
          goto joined_r0x00014070d730;
        }
        thunk_FUN_140745b50(&uStack_a0,pvVar28);
        if ((cStack_80 != '\0') && (lStack_90 != 0)) {
          acStack_108[0] = '\x01';
          thunk_FUN_1401648d0(&uStack_100,&uStack_a0);
          if (pcStack_4f8 == pcStack_4f0) {
            FUN_1406fb370(&pcStack_500);
          }
          else {
            *pcStack_4f8 = acStack_108[0];
            *(undefined4 *)(pcStack_4f8 + 8) = (undefined4)uStack_100;
            *(undefined4 *)(pcStack_4f8 + 0xc) = uStack_100._4_4_;
            *(undefined4 *)(pcStack_4f8 + 0x10) = (undefined4)uStack_f8;
            *(undefined4 *)(pcStack_4f8 + 0x14) = uStack_f8._4_4_;
            *(undefined4 *)(pcStack_4f8 + 0x18) = (undefined4)uStack_f0;
            *(undefined4 *)(pcStack_4f8 + 0x1c) = uStack_f0._4_4_;
            *(undefined4 *)(pcStack_4f8 + 0x20) = (undefined4)uStack_e8;
            *(undefined4 *)(pcStack_4f8 + 0x24) = uStack_e8._4_4_;
            uStack_f0 = 0;
            uStack_e8 = 7;
            uStack_100 = (undefined8 ******)((ulonglong)uStack_100 & 0xffffffffffff0000);
            pcStack_4f8 = pcStack_4f8 + 0x28;
          }
          thunk_FUN_14016c430(&uStack_100);
        }
        if (cStack_80 != '\0') {
          thunk_FUN_14016c430(&uStack_a0);
        }
      }
      bVar10 = false;
      bVar6 = false;
      bVar4 = false;
      sStack_490 = strlen("powershell");
      pcStack_498 = "powershell";
      thunk_FUN_140d91040(&pppppppuStack_128,&pcStack_498);
      uVar31 = uStack_118;
      if (uStack_118 == 0) goto LAB_14070d9fd;
      acStack_108[0] = '\x02';
      uStack_100 = (undefined8 ******)0x0;
      uStack_f8 = (undefined8 ******)0x0;
      uStack_f0 = 0;
      uStack_e8 = 0;
      _Src = &pppppppuStack_128;
      if (7 < uStack_110) {
        _Src = pppppppuStack_128;
      }
      if (0x7ffffffffffffffe < uStack_118) {
                    /* WARNING: Subroutine does not return */
        thunk_FUN_14016c500();
      }
      if (uStack_118 < 8) {
        uStack_f0 = uStack_118;
        uStack_e8 = 7;
        uStack_100 = *_Src;
        uStack_f8 = _Src[1];
        uVar36 = *(undefined4 *)_Src;
        uVar37 = *(undefined4 *)((longlong)_Src + 4);
        uVar38 = *(undefined4 *)(_Src + 1);
        uVar39 = *(undefined4 *)((longlong)_Src + 0xc);
      }
      else {
        uVar23 = uStack_118 | 7;
        if (uVar23 < 0x7fffffffffffffff) {
          if (uVar23 < 10) {
            uVar23 = 10;
          }
          if (0x7fffffffffffffff < uVar23 + 1) {
                    /* WARNING: Subroutine does not return */
            thunk_FUN_14016c130();
          }
          uVar30 = (uVar23 + 1) * 2;
          if (uVar30 != 0) goto LAB_14070d909;
          uStack_100 = (undefined8 ******)0x0;
        }
        else {
          uVar30 = 0xfffffffffffffffe;
          uVar23 = 0x7ffffffffffffffe;
LAB_14070d909:
          if (uVar30 < 0x1000) {
            uStack_100 = (undefined8 ******)thunk_FUN_140aba630();
          }
          else {
            uStack_100 = (undefined8 ******)thunk_FUN_14015f520();
          }
        }
        uStack_f0 = uVar31;
        uStack_e8 = uVar23;
        memcpy(uStack_100,_Src,uVar31 * 2 + 2);
        uVar36 = (undefined4)uStack_100;
        uVar37 = uStack_100._4_4_;
        uVar38 = (undefined4)uStack_f8;
        uVar39 = uStack_f8._4_4_;
      }
      if (pcStack_4f8 == pcStack_4f0) {
        FUN_1406fb370(&pcStack_500,pcStack_4f8,acStack_108);
        uVar31 = uStack_e8;
      }
      else {
        *pcStack_4f8 = '\x02';
        *(undefined4 *)(pcStack_4f8 + 8) = uVar36;
        *(undefined4 *)(pcStack_4f8 + 0xc) = uVar37;
        *(undefined4 *)(pcStack_4f8 + 0x10) = uVar38;
        *(undefined4 *)(pcStack_4f8 + 0x14) = uVar39;
        *(undefined4 *)(pcStack_4f8 + 0x18) = (undefined4)uStack_f0;
        *(undefined4 *)(pcStack_4f8 + 0x1c) = uStack_f0._4_4_;
        *(undefined4 *)(pcStack_4f8 + 0x20) = (undefined4)uStack_e8;
        *(undefined4 *)(pcStack_4f8 + 0x24) = uStack_e8._4_4_;
        uStack_100 = (undefined8 ******)((ulonglong)uStack_100 & 0xffffffffffff0000);
        pcStack_4f8 = pcStack_4f8 + 0x28;
        uVar31 = 7;
      }
      if (7 < uVar31) {
        thunk_FUN_14016a870(&uStack_100,uStack_100);
      }
      param_11 = uStack_518;
LAB_14070d9fd:
      if (7 < uStack_110) {
        if ((0xfff < uStack_110 * 2 + 2) &&
           (0x1f < (ulonglong)((longlong)pppppppuStack_128 + (-8 - (longlong)pppppppuStack_128[-1]))
           )) {
                    /* WARNING: Subroutine does not return */
          _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        FUN_14005a335();
      }
      sStack_490 = strlen("cmd");
      pcStack_498 = "cmd";
      thunk_FUN_140d91040(&pppppppuStack_128,&pcStack_498);
      if (uStack_118 != 0) {
        acStack_108[0] = '\x03';
        thunk_FUN_1401648d0(&uStack_100,&pppppppuStack_128);
        if (pcStack_4f8 == pcStack_4f0) {
          FUN_1406fb370(&pcStack_500);
        }
        else {
          *pcStack_4f8 = acStack_108[0];
          *(undefined4 *)(pcStack_4f8 + 8) = (undefined4)uStack_100;
          *(undefined4 *)(pcStack_4f8 + 0xc) = uStack_100._4_4_;
          *(undefined4 *)(pcStack_4f8 + 0x10) = (undefined4)uStack_f8;
          *(undefined4 *)(pcStack_4f8 + 0x14) = uStack_f8._4_4_;
          *(undefined4 *)(pcStack_4f8 + 0x18) = (undefined4)uStack_f0;
          *(undefined4 *)(pcStack_4f8 + 0x1c) = uStack_f0._4_4_;
          *(undefined4 *)(pcStack_4f8 + 0x20) = (undefined4)uStack_e8;
          *(undefined4 *)(pcStack_4f8 + 0x24) = uStack_e8._4_4_;
          uStack_f0 = 0;
          uStack_e8 = 7;
          uStack_100 = (undefined8 ******)((ulonglong)uStack_100 & 0xffffffffffff0000);
          pcStack_4f8 = pcStack_4f8 + 0x28;
        }
        thunk_FUN_14016c430(&uStack_100);
      }
      if (7 < uStack_110) {
        if ((0xfff < uStack_110 * 2 + 2) &&
           (0x1f < (ulonglong)((longlong)pppppppuStack_128 + (-8 - (longlong)pppppppuStack_128[-1]))
           )) {
                    /* WARNING: Subroutine does not return */
          _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        FUN_14005a335();
      }
      pcStack_508 = pcStack_4f8;
      pcStack_4d8 = pcStack_500;
      uVar32 = 0;
      bVar35 = false;
      bVar5 = false;
      bVar7 = false;
      bVar8 = false;
      bVar9 = false;
      bVar11 = false;
      bVar12 = false;
LAB_14070dba0:
      do {
        if (pcStack_4d8 == pcStack_508) goto LAB_14070f705;
        cVar15 = FUN_1407003e0(param_9);
        if (cVar15 == '\0') {
          if (cStack_3c0 != '\0') {
            thunk_FUN_14016c430(auStack_3e0);
          }
          pcVar14 = pcStack_4f8;
          pcVar20 = pcStack_500;
          if (pcStack_500 != (char *)0x0) {
            for (; pcVar20 != pcVar14; pcVar20 = pcVar20 + 0x28) {
              thunk_FUN_14016c430(pcVar20 + 8);
            }
            pcVar20 = pcStack_500;
            if ((0xfff < (ulonglong)
                         ((((longlong)pcStack_4f0 - (longlong)pcStack_500) / 0x28) * 0x28)) &&
               (pcVar20 = *(char **)(pcStack_500 + -8),
               (char *)0x1f < pcStack_500 + (-8 - (longlong)pcVar20))) {
                    /* WARNING: Subroutine does not return */
              _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
            }
            FUN_14005a335(pcVar20);
            pcStack_500 = (char *)0x0;
            pcStack_4f8 = (char *)0x0;
            pcStack_4f0 = (char *)0x0;
          }
          if (7 < uStack_c8) {
            if ((0xfff < uStack_c8 * 2 + 2) &&
               (0x1f < (uStack_e0 - *(longlong *)(uStack_e0 - 8)) - 8)) {
                    /* WARNING: Subroutine does not return */
              _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
            }
            FUN_14005a335();
          }
          uStack_d0 = 0;
          uStack_c8 = 7;
          uStack_e0 = uStack_e0 & 0xffffffffffff0000;
          if (uStack_a8 < 8) {
            return 0;
          }
          if ((0xfff < uStack_a8 * 2 + 2) &&
             (0x1f < (alStack_c0[0] - *(longlong *)(alStack_c0[0] + -8)) - 8U)) {
                    /* WARNING: Subroutine does not return */
            _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
          }
          goto LAB_14070f8b4;
        }
        cVar15 = *pcStack_4d8;
        auStack_520[0] = CONCAT11(auStack_520[0]._1_1_,cVar15);
        uVar24 = FUN_140710ec0(cVar15);
        uStack_4a8 = uVar24;
        plVar25 = (longlong *)thunk_FUN_140235d50(auStack_2e8);
        lVar33 = *plVar25 + 5000000000;
        if (lVar33 == param_9) {
          cVar16 = '\0';
        }
        else {
          cVar16 = -1;
          if (param_9 <= lVar33) {
            cVar16 = '\x01';
          }
        }
        lVar22 = param_9;
        if (cVar16 < '\0') {
          lVar22 = lVar33;
        }
        thunk_FUN_14071b800(*puStack_3a0,&uStack_4d0);
        uStack_120 = 0;
        uStack_118 = 0;
        uStack_110 = 7;
        pppppppuStack_128 = (undefined8 *******)0x0;
        cVar16 = thunk_FUN_1406faef0(&uStack_4d0,0);
        if (cVar16 == '\0') {
          puVar26 = (undefined8 *)thunk_FUN_14071dbe0(uStack_4d0);
          puStack_378 = puVar26;
          if (0xf < (ulonglong)puVar26[3]) {
            puStack_378 = (undefined8 *)*puVar26;
          }
          uStack_370 = puVar26[2];
          cVar16 = thunk_FUN_1402287e0(&puStack_378,&pppppppuStack_128);
          if (cVar16 == '\0') goto LAB_14070f55f;
          lVar33 = lStack_4e0 + 0x2b8;
          thunk_FUN_140744b60(auStack_458,alStack_c0,&uStack_e0);
          ppppppWStack_140 = (LPWSTR *****)0x0;
          ppppppWStack_138 = (LPWSTR *****)0x0;
          ppppppWStack_130 = (LPWSTR *****)0x7;
          pppppppWStack_148 = (LPWSTR ******)0x0;
          if (cStack_420 == '\0') {
LAB_14070f46f:
            thunk_FUN_14071be90(uStack_4d0);
            cVar15 = thunk_FUN_140202db0(3);
            if (cVar15 != '\0') {
              lVar33 = thunk_FUN_1402088f0(auStack_258,3,"Server.Terminal");
              uStack_524 = uVar32 | 0x20;
              if (*(char *)(lVar33 + 0xf8) != '\0') {
                thunk_FUN_14015d4f0(lVar33 + 0x10,
                                    "terminal visible attach result=fallback stage=build_command candidate="
                                   );
              }
              uVar32 = uStack_524;
              bVar4 = bVar35;
              bVar6 = bVar5;
              bVar8 = bVar7;
              bVar10 = bVar9;
              bVar12 = bVar11;
              if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                  (thunk_FUN_14015d4f0(lVar33 + 0x10,uVar24), *(char *)(lVar33 + 0xf8) != '\0')) &&
                 (thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="),
                 *(char *)(lVar33 + 0xf8) != '\0')) {
                std::basic_ostream<char,std::char_traits<char>_>::operator<<
                          ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                           *(uint *)(lStack_4e0 + 0x120));
              }
            }
            bVar34 = bVar8;
            bVar13 = bVar12;
            if ((uVar32 & 0x20) != 0) {
              uStack_524 = uVar32 & 0xffffffdf;
              thunk_FUN_140208c50(auStack_258);
              uVar32 = uStack_524;
              bVar4 = bVar35;
              bVar6 = bVar5;
              bVar34 = bVar7;
              bVar10 = bVar9;
              bVar13 = bVar11;
            }
LAB_14070e56b:
            if ((LPWSTR *****)0x7 < ppppppWStack_130) {
              thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
            }
            ppppppWStack_138 = (LPWSTR *****)0x0;
            ppppppWStack_130 = (LPWSTR *****)0x7;
            pppppppWStack_148 = (LPWSTR ******)((ulonglong)pppppppWStack_148 & 0xffffffffffff0000);
            if (cStack_420 != '\0') {
              thunk_FUN_1401c5640(auStack_438);
              thunk_FUN_14016c430(auStack_458);
            }
            if (7 < uStack_110) {
              thunk_FUN_14016a870(&pppppppuStack_128,pppppppuStack_128);
            }
            uStack_118 = 0;
            uStack_110 = 7;
            pppppppuStack_128 =
                 (undefined8 *******)((ulonglong)pppppppuStack_128 & 0xffffffffffff0000);
            if (plStack_4c8 != (longlong *)0x0) {
              thunk_FUN_14016a9a0();
            }
            goto LAB_14070f6e2;
          }
          cVar16 = *pcStack_4d8;
          if (cVar16 == '\x01') {
            if (puStack_3f0[1] == 0) {
              puVar26 = (undefined8 *)
                        thunk_FUN_1401de3f0(acStack_108,L"UU Remote Terminal - ",lVar33);
              uStack_524 = uVar32 | 8;
            }
            else {
              uStack_a0 = 0;
              uStack_98 = 0;
              lStack_90 = 0;
              uStack_88 = 0;
              thunk_FUN_14015f910(&uStack_a0,*puStack_3f0,puStack_3f0[1]);
              puVar26 = &uStack_a0;
              uStack_524 = uVar32 | 0x10;
            }
            uStack_78 = 0;
            uStack_70 = 0;
            uStack_68 = 0;
            uStack_60 = 0;
            uStack_78 = *puVar26;
            uStack_70 = puVar26[1];
            uStack_68 = puVar26[2];
            uStack_60 = puVar26[3];
            *(undefined2 *)puVar26 = 0;
            puVar26[2] = 0;
            puVar26[3] = 7;
            if ((uStack_524 & 0x10) != 0) {
              uStack_524 = uStack_524 & 0xffffffef;
              thunk_FUN_14016c430(&uStack_a0);
            }
            if ((uStack_524 & 8) != 0) {
              uStack_524 = uStack_524 & 0xfffffff7;
              thunk_FUN_14016c430(acStack_108);
            }
            pppppppWVar27 =
                 (LPWSTR ******)thunk_FUN_1407455b0(&uStack_a0,pcStack_4d8 + 8,&uStack_78);
            if (&pppppppWStack_148 != (LPWSTR *******)pppppppWVar27) {
              if ((LPWSTR *****)0x7 < ppppppWStack_130) {
                thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
              }
              pppppppWStack_148 = (LPWSTR ******)*pppppppWVar27;
              ppppppWStack_140 = pppppppWVar27[1];
              ppppppWStack_138 = pppppppWVar27[2];
              ppppppWStack_130 = pppppppWVar27[3];
              pppppppWVar27[2] = (LPWSTR *****)0x0;
              pppppppWVar27[3] = (LPWSTR *****)0x7;
              *(undefined2 *)pppppppWVar27 = 0;
            }
            thunk_FUN_14016c430(&uStack_a0);
            puVar26 = &uStack_78;
            uVar32 = uStack_524;
            bVar4 = bVar35;
            bVar6 = bVar5;
            bVar8 = bVar7;
            bVar10 = bVar9;
            bVar12 = bVar11;
          }
          else {
            if (cVar16 == '\x02') {
              pppppppWVar27 =
                   (LPWSTR ******)thunk_FUN_1407443b0(&uStack_a0,pcStack_4d8 + 8,auStack_458);
            }
            else {
              if (cVar16 != '\x03') goto LAB_14070f46f;
              pppppppWVar27 =
                   (LPWSTR ******)thunk_FUN_140743ac0(&uStack_a0,pcStack_4d8 + 8,auStack_458);
            }
            if (&pppppppWStack_148 != (LPWSTR *******)pppppppWVar27) {
              if ((LPWSTR *****)0x7 < ppppppWStack_130) {
                thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
              }
              pppppppWStack_148 = (LPWSTR ******)*pppppppWVar27;
              ppppppWStack_140 = pppppppWVar27[1];
              ppppppWStack_138 = pppppppWVar27[2];
              ppppppWStack_130 = pppppppWVar27[3];
              pppppppWVar27[2] = (LPWSTR *****)0x0;
              pppppppWVar27[3] = (LPWSTR *****)0x7;
              *(undefined2 *)pppppppWVar27 = 0;
            }
            puVar26 = &uStack_a0;
          }
          thunk_FUN_14016c430(puVar26);
          if (ppppppWStack_138 == (LPWSTR *****)0x0) goto LAB_14070f46f;
          cVar16 = thunk_FUN_140202db0(2);
          if (cVar16 != '\0') {
            lVar33 = thunk_FUN_1402088f0(auStack_258,2,"Server.Terminal");
            uStack_524 = uVar32 | 0x40;
            if (*(char *)(lVar33 + 0xf8) != '\0') {
              thunk_FUN_14015d4f0(lVar33 + 0x10,
                                  "terminal visible attach result=started stage=create_process candidate="
                                 );
            }
            if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                (thunk_FUN_14015d4f0(lVar33 + 0x10,uVar24), *(char *)(lVar33 + 0xf8) != '\0')) &&
               (thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="), *(char *)(lVar33 + 0xf8) != '\0')
               ) {
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                         *(uint *)(lStack_4e0 + 0x120));
            }
            cVar15 = (char)auStack_520[0];
            uVar32 = uStack_524;
            bVar4 = bVar35;
            bVar6 = bVar5;
            bVar8 = bVar7;
            bVar10 = bVar9;
            bVar12 = bVar11;
          }
          if ((uVar32 & 0x40) != 0) {
            uStack_524 = uVar32 & 0xffffffbf;
            thunk_FUN_140208c50(auStack_258);
            uVar32 = uStack_524;
            bVar4 = bVar35;
            bVar6 = bVar5;
            bVar8 = bVar7;
            bVar10 = bVar9;
            bVar12 = bVar11;
          }
          _Stack_2c8._4_8_ = 0;
          _Stack_2c8._12_8_ = 0;
          _Stack_2c8._20_8_ = 0;
          _Stack_2c8._28_8_ = 0;
          _Stack_2c8.dwY = 0;
          _Stack_2c8.dwXSize = 0;
          _Stack_2c8.dwYSize = 0;
          _Stack_2c8.dwXCountChars = 0;
          _Stack_2c8.dwYCountChars = 0;
          _Stack_2c8.dwFillAttribute = 0;
          _Stack_2c8.dwFlags = 0;
          _Stack_2c8.wShowWindow = 0;
          _Stack_2c8.cbReserved2 = 0;
          _Stack_2c8._68_8_ = 0;
          _Stack_2c8._76_8_ = 0;
          _Stack_2c8._84_8_ = 0;
          _Stack_2c8._92_8_ = 0;
          _Stack_2c8.hStdError._4_4_ = 0;
          _Stack_2c8.cb = 0x68;
          _Stack_398.hProcess = (HANDLE)0x0;
          _Stack_398.hThread = (HANDLE)0x0;
          _Stack_398.dwProcessId = 0;
          _Stack_398.dwThreadId = 0;
          uVar17 = 0;
          if (cVar15 != '\x01') {
            uVar17 = 0x14;
          }
          pppppppWVar27 = (LPWSTR ******)&pppppppWStack_148;
          if ((LPWSTR *****)0x7 < ppppppWStack_130) {
            pppppppWVar27 = pppppppWStack_148;
          }
          lpApplicationName = (LPCWSTR)(pcStack_4d8 + 8);
          if (7 < *(ulonglong *)(pcStack_4d8 + 0x20)) {
            lpApplicationName = *(LPCWSTR *)lpApplicationName;
          }
          BVar18 = CreateProcessAsUserW
                             (pvStack_468,lpApplicationName,(LPWSTR)pppppppWVar27,
                              (LPSECURITY_ATTRIBUTES)0x0,(LPSECURITY_ATTRIBUTES)0x0,0,
                              uVar17 | uStack_488,pcStack_408,pWStack_3f8,&_Stack_2c8,&_Stack_398);
          if (BVar18 == 0) {
            DVar19 = GetLastError();
          }
          else {
            DVar19 = 0;
          }
          bVar34 = BVar18 != 0;
          pvVar28 = (HANDLE)0x0;
          if (bVar34) {
            pvVar28 = _Stack_398.hProcess;
          }
          hThread = (HANDLE)0x0;
          if (bVar34) {
            hThread = _Stack_398.hThread;
          }
          uStack_78 = 0;
          uStack_4e8 = 0;
          pvStack_4c0 = pvVar28;
          pvStack_4b0 = hThread;
          pvStack_418 = pvVar28;
          if (!bVar34) {
            thunk_FUN_14071be90(uStack_4d0);
            cVar15 = thunk_FUN_140202db0(3);
            if (cVar15 != '\0') {
              lVar33 = thunk_FUN_1402088f0(auStack_258,3,"Server.Terminal");
              if (*(char *)(lVar33 + 0xf8) != '\0') {
                thunk_FUN_14015d4f0(lVar33 + 0x10,
                                    "terminal visible attach result=fallback stage=create_process candidate="
                                   );
              }
              if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                  (thunk_FUN_14015d4f0(lVar33 + 0x10,uStack_4a8), *(char *)(lVar33 + 0xf8) != '\0'))
                 && ((thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="),
                     *(char *)(lVar33 + 0xf8) != '\0' &&
                     (std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                                 *(uint *)(lStack_4e0 + 0x120)), *(char *)(lVar33 + 0xf8) != '\0')))
                 ) {
                thunk_FUN_14015d4f0(lVar33 + 0x10," code=");
              }
              uVar24 = thunk_FUN_140286c20(acStack_108,DVar19);
              uStack_524 = uVar32 | 0x180;
              bVar35 = true;
              uVar32 = uStack_524;
              bVar4 = bVar35;
              bVar6 = bVar5;
              bVar8 = bVar7;
              bVar10 = bVar9;
              bVar12 = bVar11;
              if (*(char *)(lVar33 + 0xf8) != '\0') {
                thunk_FUN_14015ece0(lVar33 + 0x10,uVar24);
              }
            }
            if (bVar35) {
              uStack_524 = uVar32 & 0xfffffeff;
              bVar4 = false;
              bVar35 = false;
              thunk_FUN_14016c3a0(acStack_108);
              uVar32 = uStack_524;
              bVar6 = bVar5;
              bVar8 = bVar7;
              bVar10 = bVar9;
              bVar12 = bVar11;
            }
            if ((char)uVar32 < '\0') {
              uStack_524 = uVar32 & 0xffffff7f;
              goto LAB_14070e529;
            }
LAB_14070e541:
            thunk_FUN_140166360(&uStack_4e8);
            thunk_FUN_140166360(&pvStack_4b0);
            thunk_FUN_140166360(&pvStack_4c0);
            bVar34 = bVar8;
            bVar13 = bVar12;
            goto LAB_14070e56b;
          }
          if ((char)auStack_520[0] != '\x01') {
            uStack_4b8 = uStack_4b8 & 0xffffffff00000000;
            cVar15 = FUN_1406ffc70(pvVar28,&uStack_4e8,&uStack_4b8);
            if (cVar15 == '\0') {
              thunk_FUN_14071be90(uStack_4d0);
              pcStack_368 = "assign_visible_fallback_job";
              uStack_360 = 0x1b;
              pcStack_358 = "terminal_open";
              uStack_350 = 0xd;
              FUN_140710770(pvVar28,&pcStack_358,&pcStack_368);
              cVar15 = thunk_FUN_140202db0(3);
              if (cVar15 != '\0') {
                lVar33 = thunk_FUN_1402088f0(auStack_258,3,"Server.Terminal");
                if (*(char *)(lVar33 + 0xf8) != '\0') {
                  thunk_FUN_14015d4f0(lVar33 + 0x10,
                                      "terminal visible attach result=fallback stage=assign_job candidate="
                                     );
                }
                if ((((*(char *)(lVar33 + 0xf8) != '\0') &&
                     (thunk_FUN_14015d4f0(lVar33 + 0x10,uStack_4a8),
                     *(char *)(lVar33 + 0xf8) != '\0')) &&
                    (thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="),
                    *(char *)(lVar33 + 0xf8) != '\0')) &&
                   (std::basic_ostream<char,std::char_traits<char>_>::operator<<
                              ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                               *(uint *)(lStack_4e0 + 0x120)), *(char *)(lVar33 + 0xf8) != '\0')) {
                  thunk_FUN_14015d4f0(lVar33 + 0x10," code=");
                }
                uVar24 = thunk_FUN_140286c20(acStack_108,uStack_4b8 & 0xffffffff);
                bVar8 = true;
                bVar5 = true;
                uStack_524 = uVar32;
                bVar4 = bVar35;
                bVar6 = bVar5;
                bVar7 = bVar8;
                bVar10 = bVar9;
                bVar12 = bVar11;
                if (*(char *)(lVar33 + 0xf8) != '\0') {
                  thunk_FUN_14015ece0(lVar33 + 0x10,uVar24);
                }
              }
              if (bVar5) {
                bVar6 = false;
                bVar5 = false;
                thunk_FUN_14016c3a0(acStack_108);
                uStack_524 = uVar32;
                bVar4 = bVar35;
                bVar8 = bVar7;
                bVar10 = bVar9;
                bVar12 = bVar11;
              }
              if (bVar7) {
                bVar7 = false;
                uStack_524 = uVar32;
LAB_14070e529:
                thunk_FUN_140208c50(auStack_258);
                uVar32 = uStack_524;
                bVar4 = bVar35;
                bVar6 = bVar5;
                bVar8 = bVar7;
                bVar10 = bVar9;
                bVar12 = bVar11;
              }
            }
            else {
              DVar19 = ResumeThread(hThread);
              if (DVar19 != 0xffffffff) {
                uStack_78 = uStack_4e8;
                goto LAB_14070e9d1;
              }
              DVar19 = GetLastError();
              thunk_FUN_14071be90(uStack_4d0);
              thunk_FUN_1401704a0(&uStack_4e8,0);
              pcStack_348 = "resume_visible_fallback";
              uStack_340 = 0x17;
              pcStack_338 = "terminal_open";
              uStack_330 = 0xd;
              FUN_140710770(pvVar28,&pcStack_338,&pcStack_348);
              cVar15 = thunk_FUN_140202db0(3);
              if (cVar15 != '\0') {
                lVar33 = thunk_FUN_1402088f0(auStack_258,3,"Server.Terminal");
                if (*(char *)(lVar33 + 0xf8) != '\0') {
                  thunk_FUN_14015d4f0(lVar33 + 0x10,
                                      "terminal visible attach result=fallback stage=resume candidate="
                                     );
                }
                if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                    (thunk_FUN_14015d4f0(lVar33 + 0x10,uStack_4a8), *(char *)(lVar33 + 0xf8) != '\0'
                    )) && ((thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="),
                           *(char *)(lVar33 + 0xf8) != '\0' &&
                           (std::basic_ostream<char,std::char_traits<char>_>::operator<<
                                      ((basic_ostream<char,std::char_traits<char>_> *)
                                       (lVar33 + 0x10),*(uint *)(lStack_4e0 + 0x120)),
                           *(char *)(lVar33 + 0xf8) != '\0')))) {
                  thunk_FUN_14015d4f0(lVar33 + 0x10," code=");
                }
                uVar24 = thunk_FUN_140286c20(acStack_108,DVar19);
                bVar12 = true;
                bVar9 = true;
                uStack_524 = uVar32;
                bVar4 = bVar35;
                bVar6 = bVar5;
                bVar8 = bVar7;
                bVar10 = bVar9;
                bVar11 = bVar12;
                if (*(char *)(lVar33 + 0xf8) != '\0') {
                  thunk_FUN_14015ece0(lVar33 + 0x10,uVar24);
                }
              }
              if (bVar9) {
                bVar10 = false;
                bVar9 = false;
                thunk_FUN_14016c3a0(acStack_108);
                uStack_524 = uVar32;
                bVar4 = bVar35;
                bVar6 = bVar5;
                bVar8 = bVar7;
                bVar12 = bVar11;
              }
              if (bVar11) {
                bVar11 = false;
                uStack_524 = uVar32;
                goto LAB_14070e529;
              }
            }
            goto LAB_14070e541;
          }
LAB_14070e9d1:
          uVar31 = 0;
          uStack_4b8 = 0;
          cVar15 = (char)auStack_520[0];
          uStack_4e8 = uStack_78;
          do {
            plVar25 = (longlong *)thunk_FUN_140235d50(auStack_2e0);
            if ((lVar22 <= *plVar25) ||
               (cVar16 = FUN_1407003e0(param_9,uStack_510,uStack_518), cVar16 == '\0')) break;
            plVar25 = (longlong *)thunk_FUN_140235d50(auStack_2d8);
            lVar33 = (lVar22 - *plVar25) / 1000000;
            if (lVar33 == 100) {
              cVar16 = '\0';
            }
            else {
              cVar16 = -1;
              if (lVar33 < 0x65) {
                cVar16 = '\x01';
              }
            }
            if (cVar16 < '\0') {
              lVar33 = 100;
            }
            puVar29 = (ulonglong *)thunk_FUN_14071dc10(uStack_4d0,&lStack_3b0,lVar33);
            lVar33 = lStack_3b0;
            uVar31 = *puVar29;
            *puVar29 = 0;
            uStack_4b8 = uVar31;
            if (lStack_3b0 != 0) {
              thunk_FUN_140d59270(lStack_3b0);
              FUN_14005a335(lVar33,8);
            }
            bVar35 = uVar31 == 0;
            if (!bVar35) goto LAB_14070eacc;
          } while ((cVar15 == '\x01') || (cVar16 = FUN_140702140(pvVar28), cVar16 != '\0'));
          bVar35 = uVar31 == 0;
LAB_14070eacc:
          if ((uVar31 != 0) && (cVar15 = FUN_140711840(uVar31,lVar22,param_9), cVar15 != '\0')) {
            thunk_FUN_14071be90(uStack_4d0);
            lVar33 = lStack_4e0;
            thunk_FUN_140164f60(&uStack_410,lStack_4e0 + 0x1e0);
            thunk_FUN_1406facd0(lVar33 + 0x1b8);
            if ((char)auStack_520[0] != '\x01') {
              pvStack_4c0 = (HANDLE)0x0;
              thunk_FUN_1401704a0(lVar33 + 0x1c0,pvVar28);
              uStack_4e8 = 0;
              thunk_FUN_1401704a0(lVar33 + 0x1c8);
            }
            uVar24 = *(undefined8 *)(lVar33 + 0x1b8);
            pcStack_408 = (char *)thunk_FUN_140aba630();
            if (pcStack_408 == (char *)0x0) {
              pcStack_408 = (char *)0x0;
            }
            else {
              *pcStack_408 = *pcStack_4d8;
              *(undefined8 *)(pcStack_408 + 8) = uVar24;
              *(longlong *)(pcStack_408 + 0x10) = lVar33;
              *(undefined1 **)(pcStack_408 + 0x18) = &LAB_14001b162;
            }
            bVar4 = false;
            pcStack_498 = (char *)_beginthreadex((void *)0x0,0,thunk_FUN_1406fbc50,pcStack_408,0,
                                                 (uint *)&sStack_490);
            if (pcStack_498 == (char *)0x0) {
              sStack_490 = sStack_490 & 0xffffffff00000000;
                    /* WARNING: Subroutine does not return */
              std::_Throw_Cpp_error(6);
            }
            thunk_FUN_140232710(lVar33 + 0x1d0,&pcStack_498);
            if ((int)sStack_490 != 0) {
                    /* WARNING: Subroutine does not return */
              terminate();
            }
            _Mtx_unlock(uStack_410);
            cVar15 = thunk_FUN_140202db0(2);
            if (cVar15 != '\0') {
              lVar22 = thunk_FUN_1402088f0(auStack_258,2,"Server.Terminal",
                                           "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                          );
              bVar4 = true;
              if (*(char *)(lVar22 + 0xf8) != '\0') {
                thunk_FUN_14015d4f0(lVar22 + 0x10,
                                    "terminal visible attach result=ready stage=ready candidate=");
              }
              if ((*(char *)(lVar22 + 0xf8) != '\0') &&
                 (thunk_FUN_14015d4f0(lVar22 + 0x10,uStack_4a8), *(char *)(lVar22 + 0xf8) != '\0'))
              {
                thunk_FUN_14015d4f0(lVar22 + 0x10," session_id=");
              }
              thunk_FUN_1402ab180(lVar22,lVar33 + 0x120);
            }
            if (bVar4) {
              thunk_FUN_140208c50(auStack_258);
            }
            uVar31 = uStack_4b8;
            if (uStack_4b8 != 0) {
              thunk_FUN_140d59270(uStack_4b8);
              FUN_14005a335(uVar31,8);
            }
            thunk_FUN_140166360(&uStack_4e8);
            thunk_FUN_140166360(&pvStack_4b0);
            thunk_FUN_140166360(&pvStack_4c0);
            if ((LPWSTR *****)0x7 < ppppppWStack_130) {
              thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
            }
            ppppppWStack_138 = (LPWSTR *****)0x0;
            ppppppWStack_130 = (LPWSTR *****)0x7;
            pppppppWStack_148 = (LPWSTR ******)((ulonglong)pppppppWStack_148 & 0xffffffffffff0000);
            if (cStack_420 != '\0') {
              thunk_FUN_1401c5640(auStack_438);
              thunk_FUN_14016c430(auStack_458);
            }
            if (7 < uStack_110) {
              thunk_FUN_14016a870(&pppppppuStack_128,pppppppuStack_128);
            }
            uStack_118 = 0;
            uStack_110 = 7;
            pppppppuStack_128 =
                 (undefined8 *******)((ulonglong)pppppppuStack_128 & 0xffffffffffff0000);
            if (plStack_4c8 != (longlong *)0x0) {
              thunk_FUN_14016a9a0();
            }
            if (cStack_3c0 != '\0') {
              thunk_FUN_14016c430(auStack_3e0);
            }
            pcVar14 = pcStack_4f8;
            pcVar20 = pcStack_500;
            if (pcStack_500 != (char *)0x0) {
              for (; pcVar20 != pcVar14; pcVar20 = pcVar20 + 0x28) {
                thunk_FUN_14016c430(pcVar20 + 8);
              }
              FUN_140700c50(&pcStack_500,pcStack_500,
                            ((longlong)pcStack_4f0 - (longlong)pcStack_500) / 0x28);
              pcStack_500 = (char *)0x0;
              pcStack_4f8 = (char *)0x0;
              pcStack_4f0 = (char *)0x0;
            }
            if (7 < uStack_c8) {
              thunk_FUN_14016a870(&uStack_e0,uStack_e0);
            }
            uStack_d0 = 0;
            uStack_c8 = 7;
            uStack_e0 = uStack_e0 & 0xffffffffffff0000;
            if (7 < uStack_a8) {
              thunk_FUN_14016a870(alStack_c0,alStack_c0[0]);
            }
            return 1;
          }
          thunk_FUN_14071be90(uStack_4d0);
          if (!bVar35) {
            FUN_140712f50(uVar31,5);
            thunk_FUN_140d5a840(uVar31);
          }
          if ((char)auStack_520[0] != '\x01') {
            thunk_FUN_1401704a0(&uStack_4e8,0);
            cVar15 = FUN_140702140(pvVar28);
            if (cVar15 != '\0') {
              pcStack_308 = "visible_fallback_candidate";
              uStack_300 = 0x1a;
              pcStack_2f8 = "terminal_open";
              uStack_2f0 = 0xd;
              FUN_140710770(pvVar28,&pcStack_2f8,&pcStack_308);
            }
          }
          param_11 = uStack_518;
          cVar15 = FUN_1407003e0(param_9,uStack_510,uStack_518);
          if (cVar15 == '\0') {
            if (uVar31 != 0) {
              thunk_FUN_140d59270(uVar31);
              FUN_14005a335(uVar31,8);
            }
            thunk_FUN_140166360(&uStack_4e8);
            thunk_FUN_140166360(&pvStack_4b0);
            thunk_FUN_140166360(&pvStack_4c0);
            if ((LPWSTR *****)0x7 < ppppppWStack_130) {
              thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
            }
            ppppppWStack_138 = (LPWSTR *****)0x0;
            ppppppWStack_130 = (LPWSTR *****)0x7;
            pppppppWStack_148 = (LPWSTR ******)((ulonglong)pppppppWStack_148 & 0xffffffffffff0000);
            if (cStack_420 != '\0') {
              thunk_FUN_1401c5640(auStack_438);
              thunk_FUN_14016c430(auStack_458);
            }
            if (7 < uStack_110) {
              thunk_FUN_14016a870(&pppppppuStack_128,pppppppuStack_128);
            }
            uStack_118 = 0;
            uStack_110 = 7;
            pppppppuStack_128 =
                 (undefined8 *******)((ulonglong)pppppppuStack_128 & 0xffffffffffff0000);
            if (plStack_4c8 != (longlong *)0x0) {
              thunk_FUN_14016a9a0();
            }
            if (cStack_3c0 != '\0') {
              thunk_FUN_14016c430(auStack_3e0);
            }
            pcVar14 = pcStack_4f8;
            pcVar20 = pcStack_500;
            if (pcStack_500 != (char *)0x0) {
              for (; pcVar20 != pcVar14; pcVar20 = pcVar20 + 0x28) {
                thunk_FUN_14016c430(pcVar20 + 8);
              }
              FUN_140700c50(&pcStack_500,pcStack_500,
                            ((longlong)pcStack_4f0 - (longlong)pcStack_500) / 0x28);
              pcStack_500 = (char *)0x0;
              pcStack_4f8 = (char *)0x0;
              pcStack_4f0 = (char *)0x0;
            }
            if (7 < uStack_c8) {
              thunk_FUN_14016a870(&uStack_e0,uStack_e0);
            }
            uStack_d0 = 0;
            uStack_c8 = 7;
            uStack_e0 = uStack_e0 & 0xffffffffffff0000;
            if (uStack_a8 < 8) {
              return 0;
            }
            thunk_FUN_14016a870(alStack_c0,alStack_c0[0]);
            return 0;
          }
          cVar15 = thunk_FUN_140202db0(3);
          if (cVar15 != '\0') {
            lVar33 = thunk_FUN_1402088f0(auStack_258,3,"Server.Terminal");
            uStack_524 = uStack_524 | 0x2000;
            if (*(char *)(lVar33 + 0xf8) != '\0') {
              thunk_FUN_14015d4f0(lVar33 + 0x10,
                                  "terminal visible attach result=fallback stage=wait_ready candidate="
                                 );
            }
            if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                (thunk_FUN_14015d4f0(lVar33 + 0x10,uStack_4a8), *(char *)(lVar33 + 0xf8) != '\0'))
               && (thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="),
                  *(char *)(lVar33 + 0xf8) != '\0')) {
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                         *(uint *)(lStack_4e0 + 0x120));
            }
          }
          if (uStack_524 >> 0xd != 0) {
            uStack_524 = uStack_524 & 0xffffdfff;
            thunk_FUN_140208c50(auStack_258);
          }
          if (uVar31 != 0) {
            thunk_FUN_140d59270(uVar31);
            FUN_14005a335(uVar31,8);
          }
          thunk_FUN_140166360(&uStack_4e8);
          thunk_FUN_140166360(&pvStack_4b0);
          thunk_FUN_140166360(&pvStack_4c0);
          if ((LPWSTR *****)0x7 < ppppppWStack_130) {
            thunk_FUN_14016a870(&pppppppWStack_148,pppppppWStack_148);
          }
          ppppppWStack_138 = (LPWSTR *****)0x0;
          ppppppWStack_130 = (LPWSTR *****)0x7;
          pppppppWStack_148 = (LPWSTR ******)((ulonglong)pppppppWStack_148 & 0xffffffffffff0000);
          if (cStack_420 != '\0') {
            thunk_FUN_1401c5640(auStack_438);
            thunk_FUN_14016c430(auStack_458);
          }
          if (7 < uStack_110) {
            thunk_FUN_14016a870(&pppppppuStack_128,pppppppuStack_128);
          }
          uStack_118 = 0;
          uStack_110 = 7;
          pppppppuStack_128 =
               (undefined8 *******)((ulonglong)pppppppuStack_128 & 0xffffffffffff0000);
          uVar32 = uStack_524;
          bVar35 = bVar4;
          bVar5 = bVar6;
          bVar34 = bVar8;
          bVar9 = bVar10;
          bVar13 = bVar12;
          if (plStack_4c8 != (longlong *)0x0) {
            thunk_FUN_14016a9a0();
            pcStack_4d8 = pcStack_4d8 + 0x28;
            bVar7 = bVar8;
            bVar11 = bVar12;
            goto LAB_14070dba0;
          }
        }
        else {
LAB_14070f55f:
          cVar15 = thunk_FUN_140202db0(3);
          if (cVar15 != '\0') {
            lVar33 = thunk_FUN_1402088f0(auStack_258,3);
            uStack_524 = uVar32 | 4;
            if (*(char *)(lVar33 + 0xf8) != '\0') {
              thunk_FUN_14015d4f0(lVar33 + 0x10,
                                  "terminal visible attach result=fallback stage=register_attempt candidate="
                                 );
            }
            uVar32 = uStack_524;
            bVar4 = bVar35;
            bVar6 = bVar5;
            bVar8 = bVar7;
            bVar10 = bVar9;
            bVar12 = bVar11;
            if (((*(char *)(lVar33 + 0xf8) != '\0') &&
                (thunk_FUN_14015d4f0(lVar33 + 0x10,uVar24), *(char *)(lVar33 + 0xf8) != '\0')) &&
               (thunk_FUN_14015d4f0(lVar33 + 0x10," session_id="), *(char *)(lVar33 + 0xf8) != '\0')
               ) {
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)(lVar33 + 0x10),
                         *(uint *)(lStack_4e0 + 0x120));
            }
          }
          bVar34 = bVar8;
          bVar13 = bVar12;
          if ((uVar32 & 4) != 0) {
            uStack_524 = uVar32 & 0xfffffffb;
            thunk_FUN_140208c50(auStack_258);
            uVar32 = uStack_524;
            bVar4 = bVar35;
            bVar6 = bVar5;
            bVar34 = bVar7;
            bVar10 = bVar9;
            bVar13 = bVar11;
          }
          if (7 < uStack_110) {
            if ((0xfff < uStack_110 * 2 + 2) &&
               (0x1f < (ulonglong)
                       ((longlong)pppppppuStack_128 + (-8 - (longlong)pppppppuStack_128[-1])))) {
                    /* WARNING: Subroutine does not return */
              _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
            }
            FUN_14005a335();
          }
          plVar25 = plStack_4c8;
          uStack_118 = 0;
          uStack_110 = 7;
          pppppppuStack_128 =
               (undefined8 *******)((ulonglong)pppppppuStack_128 & 0xffffffffffff0000);
          if (plStack_4c8 != (longlong *)0x0) {
            LOCK();
            plVar1 = plStack_4c8 + 1;
            lVar33 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)lVar33 == 1) {
              (**(code **)*plStack_4c8)(plStack_4c8);
              LOCK();
              piVar2 = (int *)((longlong)plVar25 + 0xc);
              iVar3 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar3 == 1) {
                (**(code **)(*plVar25 + 8))(plVar25);
              }
            }
          }
LAB_14070f6e2:
          param_11 = uStack_518;
          bVar8 = bVar7;
          bVar12 = bVar11;
        }
        pcStack_4d8 = pcStack_4d8 + 0x28;
        bVar7 = bVar8;
        bVar8 = bVar34;
        bVar11 = bVar12;
        bVar12 = bVar13;
      } while( true );
    }
  }
  cVar15 = FUN_1407003e0(param_9,param_10);
  if (cVar15 == '\0') goto LAB_14070f813;
  thunk_FUN_14016cb60(param_11,"visible_terminal_unavailable");
  if (7 < uStack_c8) {
    if ((0xfff < uStack_c8 * 2 + 2) && (0x1f < (uStack_e0 - *(longlong *)(uStack_e0 - 8)) - 8))
    goto LAB_14070f913;
    FUN_14005a335();
  }
  uStack_e0 = uStack_e0 & 0xffffffffffff0000;
  if (uStack_a8 < 8) {
    return 0;
  }
  if (uStack_a8 * 2 + 2 < 0x1000) goto LAB_14070f8b4;
  alStack_c0[0] = alStack_c0[0] - *(longlong *)(alStack_c0[0] + -8);
  goto joined_r0x00014070f985;
LAB_14070f705:
  cVar15 = FUN_1407003e0(param_9);
  if (cVar15 != '\0') {
    thunk_FUN_14016cb60(param_11,"visible_terminal_unavailable");
  }
  if (cStack_3c0 != '\0') {
    thunk_FUN_14016c430(auStack_3e0);
  }
  pcVar14 = pcStack_4f8;
  pcVar20 = pcStack_500;
  if (pcStack_500 != (char *)0x0) {
    for (; pcVar20 != pcVar14; pcVar20 = pcVar20 + 0x28) {
      thunk_FUN_14016c430(pcVar20 + 8);
    }
    pcVar20 = pcStack_500;
    if ((0xfff < (ulonglong)((((longlong)pcStack_4f0 - (longlong)pcStack_500) / 0x28) * 0x28)) &&
       (pcVar20 = *(char **)(pcStack_500 + -8),
       (char *)0x1f < pcStack_500 + (-8 - (longlong)pcVar20))) {
                    /* WARNING: Subroutine does not return */
      _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    FUN_14005a335(pcVar20);
    pcStack_500 = (char *)0x0;
    pcStack_4f8 = (char *)0x0;
    pcStack_4f0 = (char *)0x0;
  }
LAB_14070f813:
  if (7 < uStack_c8) {
    if ((0xfff < uStack_c8 * 2 + 2) && (0x1f < (uStack_e0 - *(longlong *)(uStack_e0 - 8)) - 8)) {
LAB_14070f913:
                    /* WARNING: Subroutine does not return */
      _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
    FUN_14005a335();
  }
  uStack_e0 = uStack_e0 & 0xffffffffffff0000;
  if (uStack_a8 < 8) {
    return 0;
  }
  if (uStack_a8 * 2 + 2 < 0x1000) goto LAB_14070f8b4;
  alStack_c0[0] = alStack_c0[0] - *(longlong *)(alStack_c0[0] + -8);
joined_r0x00014070f985:
  if (0x1f < alStack_c0[0] - 8U) {
    uStack_c8 = 7;
    uStack_d0 = 0;
                    /* WARNING: Subroutine does not return */
    _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
  }
LAB_14070f8b4:
  uStack_c8 = 7;
  uStack_d0 = 0;
  FUN_14005a335();
  return 0;
}

