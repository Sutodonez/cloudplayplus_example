
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Removing unreachable block (ram,0x0001407051df) */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_1407032a0(basic_ostream<char,std::char_traits<char>_> *param_1,
             basic_ostream<char,std::char_traits<char>_> *param_2,
             basic_ostream<char,std::char_traits<char>_> *param_3,int param_4,int param_5,
             undefined4 param_6,char param_7,undefined1 param_8,undefined8 param_9,longlong param_10
             ,undefined8 *******param_11,char param_12)

{
  basic_ostream<char,std::char_traits<char>_> *pbVar1;
  LPVOID pvVar2;
  longlong lVar3;
  ulonglong uVar4;
  basic_ostream<char,std::char_traits<char>_> *pbVar5;
  bool bVar6;
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList;
  undefined1 *hObject;
  HANDLE pvVar7;
  HANDLE pvVar8;
  char cVar9;
  char cVar10;
  int iVar11;
  BOOL BVar12;
  DWORD DVar13;
  undefined8 *******pppppppuVar14;
  LPVOID pvVar15;
  longlong lVar16;
  HANDLE pvVar17;
  longlong *plVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  basic_ostream<char,std::char_traits<char>_> *pbVar21;
  char *pcVar22;
  basic_ostream<char,std::char_traits<char>_> *pbVar23;
  wchar_t *pwVar24;
  undefined8 uVar25;
  LPWSTR ******lpCommandLine;
  bool bVar26;
  undefined1 auStackY_7a8 [32];
  HANDLE pvStack_740;
  HANDLE pvStack_738;
  undefined1 *puStack_730;
  HANDLE pvStack_728;
  basic_ostream<char,std::char_traits<char>_> *pbStack_720;
  undefined1 uStack_718;
  HANDLE pvStack_710;
  HANDLE pvStack_708;
  HANDLE pvStack_700;
  basic_ostream<char,std::char_traits<char>_> *apbStack_6f8 [2];
  undefined8 *******pppppppuStack_6e8;
  longlong lStack_6e0;
  int iStack_6d8;
  int iStack_6d4;
  LPVOID pvStack_6d0;
  basic_ostream<char,std::char_traits<char>_> *pbStack_6c8;
  basic_ostream<char,std::char_traits<char>_> *pbStack_6c0;
  longlong lStack_6b8;
  basic_ostream<char,std::char_traits<char>_> *pbStack_6a8;
  undefined8 uStack_6a0;
  LPPROC_THREAD_ATTRIBUTE_LIST p_Stack_698;
  DWORD DStack_690;
  undefined4 uStack_68c;
  undefined1 *puStack_688;
  basic_ostream<char,std::char_traits<char>_> *pbStack_680;
  HANDLE pvStack_678;
  undefined1 *puStack_670;
  basic_ostream<char,std::char_traits<char>_> *pbStack_668;
  HANDLE pvStack_660;
  HANDLE pvStack_658;
  HANDLE pvStack_650;
  HANDLE pvStack_648;
  _SECURITY_ATTRIBUTES _Stack_640;
  _PROCESS_INFORMATION _Stack_628;
  _STARTUPINFOW _Stack_608;
  LPPROC_THREAD_ATTRIBUTE_LIST p_Stack_5a0;
  undefined1 auStack_598 [272];
  undefined8 *******pppppppuStack_488;
  undefined8 uStack_480;
  longlong lStack_478;
  ulonglong uStack_470;
  longlong alStack_468 [2];
  longlong lStack_458;
  ulonglong uStack_450;
  basic_ostream<char,std::char_traits<char>_> *pbStack_448;
  undefined8 uStack_440;
  undefined8 uStack_438;
  ulonglong uStack_430;
  undefined8 *******pppppppuStack_428;
  undefined8 uStack_420;
  longlong lStack_418;
  ulonglong uStack_410;
  basic_ostream<char,std::char_traits<char>_> *pbStack_408;
  undefined8 uStack_400;
  undefined8 uStack_3f8;
  ulonglong uStack_3f0;
  LPWSTR ******apppppppWStack_3e8 [3];
  ulonglong uStack_3d0;
  undefined8 *******pppppppuStack_3c8;
  longlong lStack_3c0;
  longlong lStack_3b8;
  ulonglong uStack_3b0;
  undefined1 auStack_3a8 [32];
  basic_ostream<char,std::char_traits<char>_> *pbStack_388;
  undefined8 uStack_380;
  undefined1 auStack_368 [32];
  undefined1 auStack_348 [32];
  basic_ostream<char,std::char_traits<char>_> *pbStack_328;
  int iStack_320;
  undefined1 auStack_308 [32];
  undefined1 auStack_2e8 [32];
  undefined1 auStack_2c8 [80];
  undefined1 auStack_278 [32];
  undefined1 auStack_258 [32];
  undefined1 auStack_238 [32];
  undefined1 auStack_218 [32];
  undefined1 auStack_1f8 [32];
  undefined1 auStack_1d8 [32];
  undefined1 auStack_1b8 [32];
  undefined1 auStack_198 [32];
  undefined1 auStack_178 [32];
  HANDLE pvStack_158;
  HANDLE pvStack_150;
  HANDLE pvStack_148;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  ulonglong uStack_78;
  
  uStack_78 = DAT_141e01000 ^ (ulonglong)auStackY_7a8;
  iStack_6d8 = param_5;
  lStack_6b8 = param_10;
  pppppppuStack_6e8 = param_11;
  pbVar1 = param_1 + 0x138;
  apbStack_6f8[0] = param_1;
  iStack_6d4 = param_4;
  pbStack_6c0 = param_2;
  pbStack_680 = pbVar1;
  pbStack_328 = param_3;
  iVar11 = _Mtx_lock(pbVar1);
  if (iVar11 != 0) {
                    /* WARNING: Subroutine does not return */
    std::_Throw_Cpp_error(5);
  }
  if (*(int *)(param_1 + 0x184) == 0x7fffffff) {
    *(undefined4 *)(param_1 + 0x184) = 0x7ffffffe;
                    /* WARNING: Subroutine does not return */
    std::_Throw_Cpp_error(6);
  }
  param_11[2] = (undefined8 ******)0x0;
  pppppppuVar14 = param_11;
  if ((undefined8 ******)0xf < param_11[3]) {
    pppppppuVar14 = (undefined8 *******)*param_11;
  }
  *(undefined1 *)pppppppuVar14 = 0;
  cVar9 = FUN_1407003e0(param_9,param_10,param_11);
  if (cVar9 == '\0') goto LAB_1407058ef;
  pvVar15 = (LPVOID)strlen("powershell");
  pvVar2 = *(LPVOID *)(param_2 + 0x10);
  pbVar21 = param_2;
  if ((LPVOID)0xf < *(LPVOID *)(param_2 + 0x18)) {
    pbVar21 = *(basic_ostream<char,std::char_traits<char>_> **)param_2;
  }
  if ((pvVar2 != pvVar15) ||
     ((pvVar2 != (LPVOID)0x0 && (iVar11 = memcmp(pbVar21,"powershell",(size_t)pvVar2), iVar11 != 0))
     )) {
    pvVar15 = (LPVOID)strlen("cmd");
    pbVar21 = param_2;
    if ((LPVOID)0xf < *(LPVOID *)(param_2 + 0x18)) {
      pbVar21 = *(basic_ostream<char,std::char_traits<char>_> **)param_2;
    }
    if ((pvVar2 != pvVar15) ||
       ((pvVar2 != (LPVOID)0x0 &&
        (iVar11 = memcmp(pbVar21,&DAT_1416f933c,(size_t)pvVar2), iVar11 != 0)))) {
      thunk_FUN_14016cb60(param_11,"shell_not_allowed",0x11);
      goto LAB_1407058ef;
    }
  }
  if (param_12 == '\0') {
    if (param_1 + 0x298 != param_2) {
      if ((LPVOID)0xf < *(LPVOID *)(param_2 + 0x18)) {
        param_2 = *(basic_ostream<char,std::char_traits<char>_> **)param_2;
      }
      thunk_FUN_14016cb60(param_1 + 0x298,param_2,pvVar2);
    }
    *(undefined4 *)(param_1 + 0x124) = param_6;
  }
  thunk_FUN_140710c20(param_1);
  uStack_480 = 0;
  lStack_478 = 0;
  uStack_470 = 7;
  pppppppuStack_488 = (undefined8 *******)0x0;
  if (*(basic_ostream<char,std::char_traits<char>_> **)(pbStack_328 + 8) ==
      (basic_ostream<char,std::char_traits<char>_> *)0x0) {
LAB_1407034c7:
    iVar11 = 1;
    if (1 < iStack_6d4) {
      iVar11 = iStack_6d4;
    }
    iStack_6d4 = iVar11;
    iVar11 = 1;
    if (1 < iStack_6d8) {
      iVar11 = iStack_6d8;
    }
    iStack_6d8 = iVar11;
    thunk_FUN_140702090(param_1 + 0x280);
    FUN_1407017b0(alStack_468);
    cVar9 = FUN_1407003e0(param_9,param_10);
    if (cVar9 == '\0') {
LAB_14070368a:
      if (7 < uStack_450) {
        if ((0xfff < uStack_450 * 2 + 2) &&
           (0x1f < (alStack_468[0] - *(longlong *)(alStack_468[0] + -8)) - 8U)) {
LAB_1407038ae:
                    /* WARNING: Subroutine does not return */
          _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
        FUN_14005a335();
      }
      goto LAB_1407036d3;
    }
    if (lStack_458 == 0) {
      thunk_FUN_14016cb60(param_11,"bridge_exe_not_found");
      goto LAB_14070368a;
    }
    pvStack_700 = (HANDLE)0x0;
    cVar9 = thunk_FUN_1406f8ce0(param_6,&pvStack_700,param_11);
    pvStack_740 = pvStack_700;
    cVar10 = FUN_1407003e0(param_9,param_10);
    if ((cVar10 == '\0') || (cVar9 == '\0')) {
LAB_14070367f:
      thunk_FUN_140166360(&pvStack_740);
      goto LAB_14070368a;
    }
    _Stack_640.lpSecurityDescriptor = (LPVOID)0x0;
    _Stack_640.nLength = 0x18;
    _Stack_640._4_4_ = 0;
    _Stack_640.bInheritHandle = 1;
    _Stack_640._20_4_ = 0;
    pvStack_678 = (HANDLE)0x0;
    puStack_670 = (undefined1 *)0x0;
    cVar9 = FUN_1407003e0(param_9,param_10);
    if (cVar9 == '\0') goto LAB_14070367f;
    BVar12 = CreatePipe(&pvStack_678,&puStack_670,&_Stack_640,0);
    hObject = puStack_670;
    pvVar17 = pvStack_678;
    if (BVar12 == 0) {
      thunk_FUN_14016cb60(param_11,"create_stdin_pipe_failed");
      goto LAB_14070367f;
    }
    pvStack_738 = pvStack_678;
    puStack_688 = puStack_670;
    puStack_730 = puStack_670;
    cVar9 = FUN_1407003e0(param_9,param_10);
    if (cVar9 == '\0') {
      thunk_FUN_140166360(&puStack_730);
      thunk_FUN_140166360(&pvStack_738);
      goto LAB_14070367f;
    }
    BVar12 = SetHandleInformation(hObject,1,0);
    if (BVar12 == 0) {
      thunk_FUN_14016cb60(param_11,"set_stdin_pipe_flag_failed");
      thunk_FUN_140166360(&puStack_730);
      thunk_FUN_140166360(&pvStack_738);
      thunk_FUN_140166360(&pvStack_740);
      if (7 < uStack_450) {
        if ((0xfff < uStack_450 * 2 + 2) &&
           (0x1f < (alStack_468[0] - *(longlong *)(alStack_468[0] + -8)) - 8U)) goto LAB_1407038ae;
        FUN_14005a335();
      }
      if (uStack_470 < 8) goto LAB_1407058b9;
      if (0xfff < uStack_470 * 2 + 2) {
        lVar16 = (longlong)pppppppuStack_488 - (longlong)pppppppuStack_488[-1];
        goto joined_r0x000140703802;
      }
      goto LAB_14070371a;
    }
    pbStack_668 = (basic_ostream<char,std::char_traits<char>_> *)0x0;
    pvStack_660 = (HANDLE)0x0;
    cVar9 = FUN_1407003e0(param_9,param_10);
    if (cVar9 == '\0') {
      thunk_FUN_140166360(&puStack_730);
      thunk_FUN_140166360(&pvStack_738);
      thunk_FUN_140166360(&pvStack_740);
      if (7 < uStack_450) {
        if ((0xfff < uStack_450 * 2 + 2) &&
           (0x1f < (alStack_468[0] - *(longlong *)(alStack_468[0] + -8)) - 8U)) goto LAB_1407038ae;
        FUN_14005a335();
      }
    }
    else {
      BVar12 = CreatePipe(&pbStack_668,&pvStack_660,&_Stack_640,0);
      pvVar7 = pvStack_660;
      pbVar21 = pbStack_668;
      if (BVar12 == 0) {
        thunk_FUN_14016cb60(param_11,"create_stdout_pipe_failed",0x19);
      }
      else {
        pbStack_6a8 = pbStack_668;
        pbStack_720 = pbStack_668;
        pvStack_728 = pvStack_660;
        cVar9 = FUN_1407003e0(param_9,param_10);
        if (cVar9 != '\0') {
          BVar12 = SetHandleInformation(pbVar21,1,0);
          if (BVar12 == 0) {
            thunk_FUN_14016cb60(param_11,"set_stdout_pipe_flag_failed",0x1b);
          }
          else {
            pvStack_658 = (HANDLE)0x0;
            pvStack_648 = (HANDLE)0x0;
            cVar9 = FUN_1407003e0(param_9,param_10,param_11);
            if (cVar9 != '\0') {
              BVar12 = CreatePipe(&pvStack_658,&pvStack_648,&_Stack_640,0);
              pvVar8 = pvStack_658;
              if (BVar12 == 0) {
                thunk_FUN_14016cb60(param_11,"create_ctl_pipe_failed",0x16);
              }
              else {
                pvStack_708 = pvStack_658;
                pvStack_650 = pvStack_648;
                pvStack_710 = pvStack_648;
                cVar9 = FUN_1407003e0(param_9,param_10);
                if (cVar9 != '\0') {
                  BVar12 = SetHandleInformation(pvStack_650,1,0);
                  if (BVar12 == 0) {
                    thunk_FUN_14016cb60(param_11,"set_ctl_pipe_flag_failed",0x18);
                  }
                  else {
                    p_Stack_698 = (LPPROC_THREAD_ATTRIBUTE_LIST)0x0;
                    DStack_690 = 0;
                    cVar9 = FUN_140701f50(&p_Stack_698,1,param_11);
                    lpAttributeList = p_Stack_698;
                    if (cVar9 == '\0') {
                      if (p_Stack_698 == (LPPROC_THREAD_ATTRIBUTE_LIST)0x0) goto LAB_140705819;
                      DeleteProcThreadAttributeList(p_Stack_698);
                      pvVar17 = GetProcessHeap();
                    }
                    else {
                      pvStack_158 = pvVar17;
                      pvStack_150 = pvVar7;
                      pvStack_148 = pvVar8;
                      if (p_Stack_698 == (LPPROC_THREAD_ATTRIBUTE_LIST)0x0) {
                        DStack_690 = 6;
                        uVar25 = 0x1e;
                        pcVar22 = "attribute_list_not_initialized";
LAB_140703b34:
                        thunk_FUN_14016cb60(param_11,pcVar22,uVar25);
joined_r0x000140704294:
                        if (lpAttributeList == (LPPROC_THREAD_ATTRIBUTE_LIST)0x0)
                        goto LAB_140705819;
                      }
                      else {
                        BVar12 = UpdateProcThreadAttribute
                                           (p_Stack_698,0,0x20002,&pvStack_158,0x18,(PVOID)0x0,
                                            (PSIZE_T)0x0);
                        if (BVar12 == 0) {
                          DStack_690 = GetLastError();
                          uVar25 = 0x23;
                          pcVar22 = "update_attribute_handle_list_failed";
                          goto LAB_140703b34;
                        }
                        DStack_690 = 0;
                        cVar9 = FUN_1407003e0(param_9,lStack_6b8,param_11);
                        if (cVar9 != '\0') {
                          _Stack_608._4_8_ = 0;
                          _Stack_608._12_8_ = 0;
                          _Stack_608._20_8_ = 0;
                          _Stack_608._28_8_ = 0;
                          _Stack_608.dwY = 0;
                          _Stack_608.dwXSize = 0;
                          _Stack_608.dwYSize = 0;
                          _Stack_608.dwXCountChars = 0;
                          _Stack_608.dwYCountChars = 0;
                          _Stack_608.dwFillAttribute = 0;
                          _Stack_608.dwFlags = 0;
                          _Stack_608.wShowWindow = 0;
                          _Stack_608.cbReserved2 = 0;
                          _Stack_608._68_8_ = 0;
                          _Stack_608._76_8_ = 0;
                          _Stack_608._84_8_ = 0;
                          _Stack_608._92_8_ = 0;
                          _Stack_608.hStdError._4_4_ = 0;
                          _Stack_608.cb = 0x70;
                          p_Stack_5a0 = lpAttributeList;
                          uStack_b8 = 0;
                          uStack_b0 = 0;
                          uStack_a8 = 0;
                          uStack_a0 = 0;
                          uStack_98 = 0;
                          uStack_90 = 0;
                          uStack_88 = 0;
                          uStack_80 = 0;
                          uStack_138 = 0;
                          uStack_130 = 0;
                          uStack_128 = 0;
                          uStack_120 = 0;
                          uStack_118 = 0;
                          uStack_110 = 0;
                          uStack_108 = 0;
                          uStack_100 = 0;
                          uStack_f8 = 0;
                          uStack_f0 = 0;
                          uStack_e8 = 0;
                          uStack_e0 = 0;
                          uStack_d8 = 0;
                          uStack_d0 = 0;
                          uStack_c8 = 0;
                          uStack_c0 = 0;
                          thunk_FUN_1406fcd50(&uStack_138,L"0x%IX",pvVar17);
                          thunk_FUN_1406fcd50(&uStack_f8,L"0x%IX",pvVar7);
                          thunk_FUN_1406fcd50(&uStack_b8,L"0x%IX",pvVar8);
                          thunk_FUN_140229fb0(auStack_308,iStack_6d8);
                          thunk_FUN_140229fb0(auStack_258,iStack_6d4);
                          pvVar15 = (LPVOID)strlen("cmd");
                          pvVar2 = *(LPVOID *)(pbStack_6c0 + 0x10);
                          pbVar21 = pbStack_6c0;
                          if ((LPVOID)0xf < *(LPVOID *)(pbStack_6c0 + 0x18)) {
                            pbVar21 = *(basic_ostream<char,std::char_traits<char>_> **)pbStack_6c0;
                          }
                          if (pvVar2 == pvVar15) {
                            if (pvVar2 == (LPVOID)0x0) {
                              bVar26 = true;
                            }
                            else {
                              iVar11 = memcmp(pbVar21,&DAT_1416f933c,(size_t)pvVar2);
                              bVar26 = iVar11 == 0;
                            }
                          }
                          else {
                            bVar26 = false;
                          }
                          pwVar24 = L"powershell";
                          if (bVar26) {
                            pwVar24 = L"cmd";
                          }
                          if (lStack_458 == 0x7ffffffffffffffe) {
                    /* WARNING: Subroutine does not return */
                            thunk_FUN_14016c500();
                          }
                          thunk_FUN_140164d00(auStack_278,uStack_718,alStack_468,&DAT_1416da9fc);
                          uVar25 = thunk_FUN_14015ee40(auStack_3a8,auStack_278,&DAT_1416da9fc);
                          uVar25 = thunk_FUN_14015ee40(auStack_2e8,uVar25,L" --shell ");
                          uVar25 = thunk_FUN_14015ee40(auStack_368,uVar25,pwVar24);
                          uVar25 = thunk_FUN_14015ee40(auStack_198,uVar25,L" --cols ");
                          thunk_FUN_140164a80(&pbStack_388,uStack_718,uVar25,auStack_258);
                          uVar25 = thunk_FUN_14015ee40(auStack_1b8,&pbStack_388,L" --rows ");
                          thunk_FUN_140164a80(&pbStack_328,uStack_718,uVar25,auStack_308);
                          bVar26 = false;
                          uVar25 = thunk_FUN_14015ee40(auStack_1d8,&pbStack_328,L" --stdin-handle ")
                          ;
                          uVar25 = thunk_FUN_14015ee40(auStack_1f8,uVar25,&uStack_138);
                          uVar25 = thunk_FUN_14015ee40(auStack_218,uVar25,L" --stdout-handle ");
                          uVar25 = thunk_FUN_14015ee40(auStack_178,uVar25,&uStack_f8);
                          uVar25 = thunk_FUN_14015ee40(auStack_238,uVar25,L" --ctl-handle ");
                          thunk_FUN_14015ee40(apppppppWStack_3e8,uVar25,&uStack_b8);
                          thunk_FUN_14016c430(auStack_238);
                          thunk_FUN_14016c430(auStack_178);
                          thunk_FUN_14016c430(auStack_218);
                          thunk_FUN_14016c430(auStack_1f8);
                          thunk_FUN_14016c430(auStack_1d8);
                          thunk_FUN_14016c430(&pbStack_328);
                          thunk_FUN_14016c430(auStack_1b8);
                          thunk_FUN_14016c430(&pbStack_388);
                          thunk_FUN_14016c430(auStack_198);
                          thunk_FUN_14016c430(auStack_368);
                          thunk_FUN_14016c430(auStack_2e8);
                          thunk_FUN_14016c430(auStack_3a8);
                          thunk_FUN_14016c430(auStack_278);
                          thunk_FUN_14016c430(auStack_258);
                          thunk_FUN_14016c430(auStack_308);
                          lVar16 = lStack_6b8;
                          pvStack_6d0 = (LPVOID)0x0;
                          cVar9 = FUN_1407003e0(param_9,lStack_6b8,param_11);
                          if (cVar9 == '\0') {
LAB_1407057ed:
                            thunk_FUN_14016c430(apppppppWStack_3e8);
                            goto LAB_1407057fb;
                          }
                          iVar11 = CreateEnvironmentBlock(&pvStack_6d0,pvStack_700,0);
                          if (iVar11 == 0) {
                            DVar13 = GetLastError();
                            pbStack_388 = (basic_ostream<char,std::char_traits<char>_> *)
                                          CONCAT44(pbStack_388._4_4_,DVar13);
                          }
                          else {
                            pbStack_388 = (basic_ostream<char,std::char_traits<char>_> *)
                                          ((ulonglong)pbStack_388 & 0xffffffff00000000);
                          }
                          pbStack_328 = (basic_ostream<char,std::char_traits<char>_> *)&pvStack_6d0;
                          FUN_1406fca40(auStack_2c8,&pbStack_328);
                          cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                          if (cVar9 == '\0') {
LAB_1407057df:
                            thunk_FUN_140276ae0(auStack_2c8);
                            goto LAB_1407057ed;
                          }
                          if ((iVar11 == 0) || (pvStack_6d0 == (LPVOID)0x0)) {
                            thunk_FUN_1401e0da0(auStack_308,(ulonglong)pbStack_388 & 0xffffffff);
                            thunk_FUN_1401723c0(auStack_3a8,"create_user_environment_failed_",
                                                auStack_308);
                            thunk_FUN_1401671f0(param_11);
                            thunk_FUN_14016c3a0(auStack_3a8);
                            thunk_FUN_14016c3a0(auStack_308);
                            goto LAB_1407057df;
                          }
                          uStack_440 = 0;
                          uStack_438 = 0;
                          uStack_430 = 7;
                          pbStack_448 = (basic_ostream<char,std::char_traits<char>_> *)0x0;
                          pbStack_6c0 = (basic_ostream<char,std::char_traits<char>_> *)0x0;
                          cVar9 = thunk_FUN_1406fa130(pvStack_700,&pbStack_448);
                          if (cVar9 == '\0') {
LAB_1407040c3:
                            bVar6 = false;
                          }
                          else {
                            thunk_FUN_140160070(auStack_308,&pbStack_448,0);
                            bVar26 = true;
                            cVar9 = thunk_FUN_140217b50(auStack_308);
                            if (cVar9 == '\0') goto LAB_1407040c3;
                            bVar6 = true;
                          }
                          if (bVar26) {
                            thunk_FUN_14016c430(auStack_308);
                          }
                          if ((bVar6) &&
                             (pbStack_6c0 = (basic_ostream<char,std::char_traits<char>_> *)
                                            &pbStack_448, 7 < uStack_430)) {
                            pbStack_6c0 = pbStack_448;
                          }
                          cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                          if (cVar9 == '\0') {
LAB_140704119:
                            if (7 < uStack_430) {
                              thunk_FUN_14016a870(&pbStack_448);
                            }
                            uStack_438 = 0;
                            uStack_430 = 7;
                            pbStack_448 = (basic_ostream<char,std::char_traits<char>_> *)
                                          ((ulonglong)pbStack_448 & 0xffffffffffff0000);
                            goto LAB_1407057df;
                          }
                          thunk_FUN_1406f9af0();
                          cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                          pbVar21 = apbStack_6f8[0];
                          if (cVar9 == '\0') goto LAB_140704119;
                          if (param_12 == '\0') {
                            plVar18 = (longlong *)thunk_FUN_140701ac0();
                            pbVar21 = apbStack_6f8[0];
                          }
                          else {
                            plVar18 = (longlong *)
                                      thunk_FUN_1401648d0(auStack_2e8,apbStack_6f8[0] + 0x2d8);
                          }
                          pppppppuStack_3c8 = (undefined8 *******)*plVar18;
                          lStack_3c0 = plVar18[1];
                          lVar3 = plVar18[2];
                          uVar4 = plVar18[3];
                          *(undefined2 *)plVar18 = 0;
                          plVar18[2] = 0;
                          plVar18[3] = 7;
                          lStack_3b8 = lVar3;
                          uStack_3b0 = uVar4;
                          if (param_12 == '\0') {
                            thunk_FUN_14016c430(auStack_3a8);
                          }
                          else {
                            thunk_FUN_14016c430(auStack_2e8);
                          }
                          bVar6 = false;
                          bVar26 = false;
                          cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                          if (cVar9 == '\0') {
LAB_14070421c:
                            if (7 < uVar4) {
                              thunk_FUN_14016a870(&pppppppuStack_3c8);
                            }
                            if (7 < uStack_430) {
                              thunk_FUN_14016a870(&pbStack_448);
                            }
                          }
                          else {
                            if (lVar3 == 0) {
                              thunk_FUN_14016cb60(param_11,"uuyc_mux_exe_not_found",0x16);
                              goto LAB_14070421c;
                            }
                            uStack_420 = 0;
                            lStack_418 = 0;
                            uStack_410 = 7;
                            pppppppuStack_428 = (undefined8 *******)0x0;
                            if (param_12 == '\0') {
                              cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                              if (((cVar9 != '\0') &&
                                  (cVar9 = FUN_140706760(pvStack_700,param_8,&pppppppuStack_428,
                                                         param_11), cVar9 != '\0')) &&
                                 (cVar9 = FUN_1407003e0(param_9,lVar16,param_11), cVar9 != '\0')) {
LAB_14070443f:
                                thunk_FUN_1401648d0(auStack_368,&pppppppuStack_3c8);
                                thunk_FUN_1401648d0(auStack_348,&pppppppuStack_428);
                                uStack_400 = 0;
                                uStack_3f8 = 0;
                                uStack_3f0 = 7;
                                pbStack_408 = (basic_ostream<char,std::char_traits<char>_> *)0x0;
                                if (param_12 == '\0') {
                                  cVar9 = FUN_1407008d0(pvStack_700,pvStack_6d0,pbStack_6c0);
                                  if (cVar9 != '\0') goto LAB_140704711;
                                  if (7 < uStack_3f0) {
                                    thunk_FUN_14016a870(&pbStack_408);
                                  }
                                  uStack_3f8 = 0;
                                  uStack_3f0 = 7;
                                  pbStack_408 = (basic_ostream<char,std::char_traits<char>_> *)
                                                ((ulonglong)pbStack_408 & 0xffffffffffff0000);
                                  thunk_FUN_14016c430(auStack_348);
                                  thunk_FUN_14016c430(auStack_368);
                                  if (7 < uStack_410) {
                                    thunk_FUN_14016a870(&pppppppuStack_428);
                                  }
                                  lStack_418 = 0;
                                  uStack_410 = 7;
                                  pppppppuStack_428 =
                                       (undefined8 *******)
                                       ((ulonglong)pppppppuStack_428 & 0xffffffffffff0000);
                                }
                                else {
                                  pbVar23 = pbVar21 + 0x2b8;
                                  if ((basic_ostream<char,std::char_traits<char>_> *)&pbStack_408 !=
                                      pbVar23) {
                                    if ((basic_ostream<char,std::char_traits<char>_> *)0x7 <
                                        *(basic_ostream<char,std::char_traits<char>_> **)
                                         (pbVar21 + 0x2d0)) {
                                      pbVar23 = *(basic_ostream<char,std::char_traits<char>_> **)
                                                 pbVar23;
                                    }
                                    thunk_FUN_14016cd20(&pbStack_408,pbVar23,
                                                        *(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x2c8));
                                  }
                                  cVar9 = thunk_FUN_14070c8c0(pvStack_700,pvStack_6d0,pbStack_6c0);
                                  if (cVar9 != '\0') {
LAB_140704711:
                                    uVar25 = thunk_FUN_140746b10(auStack_2e8,&pbStack_408);
                                    puVar19 = (undefined8 *)
                                              thunk_FUN_14020b3f0(auStack_3a8,
                                                                  L" --uuyc-mux-session ",uVar25);
                                    puVar20 = puVar19 + 2;
                                    if (7 < (ulonglong)puVar19[3]) {
                                      puVar19 = (undefined8 *)*puVar19;
                                    }
                                    thunk_FUN_14016c8a0(apppppppWStack_3e8,puVar19,*puVar20);
                                    thunk_FUN_14016c430(auStack_3a8);
                                    thunk_FUN_14016c430(auStack_2e8);
                                    uVar25 = thunk_FUN_140746b10(auStack_2e8,&pppppppuStack_428);
                                    puVar19 = (undefined8 *)
                                              thunk_FUN_14020b3f0(auStack_3a8,L" --uuyc-mux-config "
                                                                  ,uVar25);
                                    puVar20 = puVar19 + 2;
                                    if (7 < (ulonglong)puVar19[3]) {
                                      puVar19 = (undefined8 *)*puVar19;
                                    }
                                    thunk_FUN_14016c8a0(apppppppWStack_3e8,puVar19,*puVar20);
                                    thunk_FUN_14016c430(auStack_3a8);
                                    thunk_FUN_14016c430(auStack_2e8);
                                    if (param_12 != '\0') {
                                      thunk_FUN_14016c8a0(apppppppWStack_3e8,
                                                          L" --uuyc-mux-attach-existing",0x1b);
                                    }
                                    if (lStack_478 != 0) {
                                      uVar25 = thunk_FUN_140746b10(auStack_2e8,&pppppppuStack_488);
                                      puVar19 = (undefined8 *)
                                                thunk_FUN_14020b3f0(auStack_3a8,L" --display-name ",
                                                                    uVar25);
                                      puVar20 = puVar19 + 2;
                                      if (7 < (ulonglong)puVar19[3]) {
                                        puVar19 = (undefined8 *)*puVar19;
                                      }
                                      thunk_FUN_14016c8a0(apppppppWStack_3e8,puVar19,*puVar20);
                                      thunk_FUN_14016c430(auStack_3a8);
                                      thunk_FUN_14016c430(auStack_2e8);
                                    }
                                    if (param_12 == '\0') {
                                      if (pbVar21 + 0x2b8 !=
                                          (basic_ostream<char,std::char_traits<char>_> *)
                                          &pbStack_408) {
                                        pbVar23 = (basic_ostream<char,std::char_traits<char>_> *)
                                                  &pbStack_408;
                                        if (7 < uStack_3f0) {
                                          pbVar23 = pbStack_408;
                                        }
                                        thunk_FUN_14016cd20(pbVar21 + 0x2b8,pbVar23,uStack_3f8);
                                      }
                                      if (pbVar21 + 0x2d8 !=
                                          (basic_ostream<char,std::char_traits<char>_> *)
                                          &pppppppuStack_3c8) {
                                        pppppppuVar14 = &pppppppuStack_3c8;
                                        if (7 < uStack_3b0) {
                                          pppppppuVar14 = pppppppuStack_3c8;
                                        }
                                        thunk_FUN_14016cd20(pbVar21 + 0x2d8,pppppppuVar14,lStack_3b8
                                                           );
                                      }
                                      if (pbVar21 + 0x2f8 !=
                                          (basic_ostream<char,std::char_traits<char>_> *)
                                          &pppppppuStack_428) {
                                        pppppppuVar14 = &pppppppuStack_428;
                                        if (7 < uStack_410) {
                                          pppppppuVar14 = pppppppuStack_428;
                                        }
                                        thunk_FUN_14016cd20(pbVar21 + 0x2f8,pppppppuVar14,lStack_418
                                                           );
                                      }
                                    }
                                    cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                                    if (cVar9 != '\0') {
                                      _Stack_628.hProcess =
                                           (basic_ostream<char,std::char_traits<char>_> *)0x0;
                                      _Stack_628.hThread =
                                           (basic_ostream<char,std::char_traits<char>_> *)0x0;
                                      _Stack_628.dwProcessId = 0;
                                      _Stack_628.dwThreadId = 0;
                                      lpCommandLine = (LPWSTR ******)apppppppWStack_3e8;
                                      if (7 < uStack_3d0) {
                                        lpCommandLine = apppppppWStack_3e8[0];
                                      }
                                      BVar12 = CreateProcessAsUserW
                                                         (pvStack_700,(LPCWSTR)0x0,
                                                          (LPWSTR)lpCommandLine,
                                                          (LPSECURITY_ATTRIBUTES)0x0,
                                                          (LPSECURITY_ATTRIBUTES)0x0,1,0x80408,
                                                          pvStack_6d0,(LPCWSTR)pbStack_6c0,
                                                          &_Stack_608,&_Stack_628);
                                      if (BVar12 == 0) {
                                        DVar13 = GetLastError();
                                        pbStack_388 = (basic_ostream<char,std::char_traits<char>_> *
                                                      )CONCAT44(pbStack_388._4_4_,DVar13);
                                      }
                                      else {
                                        pbStack_388 = (basic_ostream<char,std::char_traits<char>_> *
                                                      )((ulonglong)pbStack_388 & 0xffffffff00000000)
                                        ;
                                      }
                                      apbStack_6f8[0] =
                                           (basic_ostream<char,std::char_traits<char>_> *)0x0;
                                      pbStack_6c8 = apbStack_6f8[0];
                                      if (BVar12 != 0) {
                                        pbStack_6c8 = _Stack_628.hThread;
                                        apbStack_6f8[0] = _Stack_628.hProcess;
                                      }
                                      pbStack_328 = apbStack_6f8[0];
                                      cVar9 = FUN_1407003e0(param_9,lVar16,param_11);
                                      if (cVar9 == '\0') {
                                        if (pbStack_328 + -1 <
                                            (basic_ostream<char,std::char_traits<char>_> *)
                                            0xfffffffffffffffe) {
                                          pppppppuStack_6e8 = (undefined8 *******)0x1416faa60;
                                          lStack_6e0 = 0xd;
                                          pbStack_6a8 = (basic_ostream<char,std::char_traits<char>_>
                                                         *)0x1416f98c8;
                                          uStack_6a0 = 0xd;
                                          FUN_140710770(pbStack_328,&pbStack_6a8,&pppppppuStack_6e8)
                                          ;
                                        }
                                      }
                                      else if (BVar12 == 0) {
                                        thunk_FUN_1401e0da0(auStack_308,
                                                            (ulonglong)pbStack_388 & 0xffffffff);
                                        thunk_FUN_1401723c0(auStack_3a8,
                                                            "create_bridge_process_failed_",
                                                            auStack_308);
                                        thunk_FUN_1401671f0(param_11);
                                        thunk_FUN_14016c3a0(auStack_3a8);
                                        thunk_FUN_14016c3a0(auStack_308);
                                      }
                                      else {
                                        cVar9 = thunk_FUN_140202db0(2);
                                        if (cVar9 != '\0') {
                                          lStack_6b8 = thunk_FUN_1402088f0(auStack_598,2,
                                                                           "Server.Terminal",
                                                                                                                                                      
                                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                                  );
                                          if (*(char *)(lStack_6b8 + 0xf8) != '\0') {
                                            thunk_FUN_14015d4f0(lStack_6b8 + 0x10,
                                                                                                                                
                                                  "terminal bridge result=started operation=terminal_open session_id="
                                                  );
                                          }
                                          lStack_6b8 = thunk_FUN_1402ab180(lStack_6b8,
                                                                           pbVar21 + 0x120);
                                          pbStack_388 = (basic_ostream<char,std::char_traits<char>_>
                                                         *)(lStack_6b8 + 0x10);
                                          if (*(char *)(lStack_6b8 + 0xf8) != '\0') {
                                            thunk_FUN_14015d4f0(pbStack_388," pid=");
                                          }
                                          if (*(char *)(lStack_6b8 + 0xf8) != '\0') {
                                            std::basic_ostream<char,std::char_traits<char>_>::
                                            operator<<(pbStack_388,_Stack_628.dwProcessId);
                                            if (*(char *)(lStack_6b8 + 0xf8) != '\0') {
                                              thunk_FUN_14015d4f0(pbStack_388," mux_session=");
                                            }
                                          }
                                          pbStack_388 = (basic_ostream<char,std::char_traits<char>_>
                                                         *)&pbStack_408;
                                          if (7 < uStack_3f0) {
                                            pbStack_388 = pbStack_408;
                                          }
                                          uStack_380 = uStack_3f8;
                                          uVar25 = thunk_FUN_140228850(auStack_3a8,&pbStack_388);
                                          bVar6 = true;
                                          bVar26 = true;
                                          thunk_FUN_14015ed30(lStack_6b8,uVar25);
                                        }
                                        if (bVar26) {
                                          thunk_FUN_14016c3a0(auStack_3a8);
                                        }
                                        if (bVar6) {
                                          thunk_FUN_140208c50(auStack_598);
                                        }
                                        bVar6 = false;
                                        bVar26 = false;
                                        thunk_FUN_1401704a0(&pvStack_738,0);
                                        thunk_FUN_1401704a0(&pvStack_728,0);
                                        thunk_FUN_1401704a0(&pvStack_708,0);
                                        puStack_730 = (undefined1 *)0x0;
                                        thunk_FUN_1401704a0(pbVar21 + 0x188,puStack_688);
                                        pbStack_720 = (basic_ostream<char,std::char_traits<char>_> *
                                                      )0x0;
                                        thunk_FUN_1401704a0(pbVar21 + 400,pbStack_6a8);
                                        pvStack_710 = (HANDLE)0x0;
                                        thunk_FUN_1401704a0(pbVar21 + 0x198,pvStack_650);
                                        apbStack_6f8[0] =
                                             (basic_ostream<char,std::char_traits<char>_> *)0x0;
                                        thunk_FUN_1401704a0(pbVar21 + 0x1a0,pbStack_328);
                                        thunk_FUN_1401704a0(&pbStack_6c8,0);
                                        if ((param_7 != '\0') || (param_12 != '\0')) {
                                          thunk_FUN_140741c70(pbVar21);
                                        }
                                        if (((*(basic_ostream<char,std::char_traits<char>_> **)
                                               (pbVar21 + 400) !=
                                              (basic_ostream<char,std::char_traits<char>_> *)0x0) &&
                                            (*(basic_ostream<char,std::char_traits<char>_> **)
                                              (pbVar21 + 400) !=
                                             (basic_ostream<char,std::char_traits<char>_> *)
                                             0xffffffffffffffff)) &&
                                           (*(int *)(pbVar21 + 0x1b0) == 0)) {
                                          puStack_688 = &LAB_1400412a9;
                                          pbStack_6a8 = pbVar21;
                                          puVar20 = (undefined8 *)
                                                    thunk_FUN_1406fa840(&pbStack_328,&puStack_688,
                                                                        &pbStack_6a8);
                                          if (*(int *)(pbVar21 + 0x1b0) != 0) {
LAB_140704df0:
                    /* WARNING: Subroutine does not return */
                                            terminate();
                                          }
                                          pbVar23 = (basic_ostream<char,std::char_traits<char>_> *)
                                                    *puVar20;
                                          pbVar5 = (basic_ostream<char,std::char_traits<char>_> *)
                                                   puVar20[1];
                                          *puVar20 = 0;
                                          puVar20[1] = 0;
                                          *(basic_ostream<char,std::char_traits<char>_> **)
                                           (pbVar21 + 0x1a8) = pbVar23;
                                          *(basic_ostream<char,std::char_traits<char>_> **)
                                           (pbVar21 + 0x1b0) = pbVar5;
                                          if (iStack_320 != 0) goto LAB_140704df0;
                                        }
                                        cVar9 = thunk_FUN_140202db0(2);
                                        if (cVar9 != '\0') {
                                          pppppppuStack_6e8 =
                                               (undefined8 *******)
                                               thunk_FUN_1402088f0(auStack_598,2,"Server.Terminal",
                                                                                                                                      
                                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                                  );
                                          if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                            thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                                                                                
                                                  "terminal uuyc_mux ready result=started operation=terminal_open stage=initial_ready session_id="
                                                  );
                                          }
                                          pppppppuStack_6e8 =
                                               (undefined8 *******)
                                               thunk_FUN_1402ab180(pppppppuStack_6e8,pbVar21 + 0x120
                                                                  );
                                          if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                            thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                " mux_session=");
                                          }
                                          pbStack_6a8 = (basic_ostream<char,std::char_traits<char>_>
                                                         *)&pbStack_408;
                                          if (7 < uStack_3f0) {
                                            pbStack_6a8 = pbStack_408;
                                          }
                                          uStack_6a0 = uStack_3f8;
                                          uVar25 = thunk_FUN_140228850(auStack_3a8,&pbStack_6a8);
                                          bVar6 = true;
                                          bVar26 = true;
                                          thunk_FUN_14015ed30(pppppppuStack_6e8,uVar25);
                                        }
                                        if (bVar26) {
                                          thunk_FUN_14016c3a0(auStack_3a8);
                                        }
                                        if (bVar6) {
                                          thunk_FUN_140208c50(auStack_598);
                                        }
                                        bVar26 = false;
                                        if (param_12 == '\0') {
                                          cVar9 = FUN_140711670(*(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x1a0),pvStack_700,pvStack_6d0,
                                                  pbStack_6c0);
                                          if (cVar9 != '\0') goto LAB_1407050c1;
                                        }
                                        else {
                                          pbStack_388 = (basic_ostream<char,std::char_traits<char>_>
                                                         *)((ulonglong)pbStack_388 &
                                                           0xffffffff00000000);
                                          cVar9 = FUN_140706fa0(pvStack_700,pvStack_6d0,pbStack_6c0,
                                                                auStack_368);
                                          if ((cVar9 == '\0') || ((int)pbStack_388 != 1)) {
                                            if (param_11[2] != (undefined8 ******)0x0)
                                            goto LAB_140705660;
                                            uVar25 = 0x20;
                                            pcVar22 = "terminal_mux_session_unavailable";
                                          }
                                          else {
LAB_1407050c1:
                                            cVar9 = thunk_FUN_140202db0(2);
                                            if (cVar9 != '\0') {
                                              pppppppuStack_6e8 =
                                                   (undefined8 *******)
                                                   thunk_FUN_1402088f0(auStack_598,2,
                                                                       "Server.Terminal",
                                                                                                                                              
                                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                                  );
                                              if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                                thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                                                                                        
                                                  "terminal uuyc_mux ready result=success operation=terminal_open stage=initial_ready session_id="
                                                  );
                                              }
                                              pppppppuStack_6e8 =
                                                   (undefined8 *******)
                                                   thunk_FUN_1402ab180(pppppppuStack_6e8,
                                                                       pbVar21 + 0x120);
                                              if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                                thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                    " mux_session=");
                                              }
                                              pbStack_6a8 = (
                                                  basic_ostream<char,std::char_traits<char>_> *)
                                                  &pbStack_408;
                                              if (7 < uStack_3f0) {
                                                pbStack_6a8 = pbStack_408;
                                              }
                                              uStack_6a0 = uStack_3f8;
                                              uVar25 = thunk_FUN_140228850(auStack_3a8,&pbStack_6a8)
                                              ;
                                              bVar26 = true;
                                              thunk_FUN_14015ed30(pppppppuStack_6e8,uVar25);
                                            }
                                            if (bVar26) {
                                              thunk_FUN_14016c3a0(auStack_3a8);
                                            }
                                            bVar6 = false;
                                            bVar26 = false;
                                            if ((param_12 == '\0') && (param_7 != '\0')) {
                                              pppppppuStack_6e8 = &pppppppuStack_488;
                                              if (7 < uStack_470) {
                                                pppppppuStack_6e8 = pppppppuStack_488;
                                              }
                                              lStack_6e0 = lStack_478;
                                              cVar9 = thunk_FUN_14070d3d0(pbVar21,pvStack_700,
                                                                          pvStack_6d0,0x400);
                                              if (cVar9 == '\0') goto LAB_140705660;
                                              cVar9 = thunk_FUN_140202db0(2);
                                              if (cVar9 != '\0') {
                                                pppppppuStack_6e8 =
                                                     (undefined8 *******)
                                                     thunk_FUN_1402088f0(auStack_598,2,
                                                                         "Server.Terminal",
                                                                                                                                                  
                                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                                  );
                                                if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                                  thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                                                                                            
                                                  "terminal uuyc_mux ready result=success operation=terminal_open stage=visible_ready session_id="
                                                  );
                                                }
                                                pppppppuStack_6e8 =
                                                     (undefined8 *******)
                                                     thunk_FUN_1402ab180(pppppppuStack_6e8,
                                                                         pbVar21 + 0x120);
                                                if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                                  thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                      " mux_session=");
                                                }
                                                pbStack_6a8 = (
                                                  basic_ostream<char,std::char_traits<char>_> *)
                                                  &pbStack_408;
                                                if (7 < uStack_3f0) {
                                                  pbStack_6a8 = pbStack_408;
                                                }
                                                uStack_6a0 = uStack_3f8;
                                                uVar25 = thunk_FUN_140228850(auStack_3a8,
                                                                             &pbStack_6a8);
                                                bVar6 = true;
                                                bVar26 = true;
                                                thunk_FUN_14015ed30(pppppppuStack_6e8,uVar25);
                                              }
                                              if (bVar26) {
                                                thunk_FUN_14016c3a0(auStack_3a8);
                                              }
                                              if (bVar6) {
                                                thunk_FUN_140208c50(auStack_598);
                                              }
                                            }
                                            bVar26 = false;
                                            cVar9 = thunk_FUN_140665ab0(pbVar21 + 0x110,0);
                                            if (((cVar9 == '\0') &&
                                                (cVar9 = thunk_FUN_140716380(*(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x110)), cVar9 == '\0')) &&
                                               (cVar9 = thunk_FUN_140715f60(*(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x110),pvStack_700,
                                                  *(undefined4 *)(pbVar21 + 0x124)), cVar9 == '\0'))
                                            {
                                              cVar9 = thunk_FUN_140202db0(3);
                                              if (cVar9 != '\0') {
                                                pppppppuStack_6e8 =
                                                     (undefined8 *******)
                                                     thunk_FUN_1402088f0(auStack_598,3,
                                                                         "Server.Terminal",
                                                                                                                                                  
                                                  "D:\\nrd-windows-client-gitlab\\work\\1131\\408844\\source\\src\\server_core\\business\\terminal\\terminal_session.cpp"
                                                  );
                                                bVar26 = true;
                                                if (*(char *)(pppppppuStack_6e8 + 0x1f) != '\0') {
                                                  thunk_FUN_14015d4f0(pppppppuStack_6e8 + 2,
                                                                                                                                            
                                                  "terminal mux control result=failed stage=start session_id="
                                                  );
                                                }
                                                thunk_FUN_1402ab180(pppppppuStack_6e8,
                                                                    pbVar21 + 0x120);
                                              }
                                              if (bVar26) {
                                                thunk_FUN_140208c50(auStack_598);
                                              }
                                            }
                                            cVar9 = FUN_140702140(*(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x1a0));
                                            cVar10 = FUN_1407003e0(param_9,lVar16,param_11);
                                            if (cVar10 == '\0') {
                                              if (cVar9 == '\0') goto LAB_140705614;
                                            }
                                            else {
                                              if (cVar9 != '\0') {
                                                thunk_FUN_140166360(&pbStack_6c8);
                                                thunk_FUN_140166360(apbStack_6f8);
                                                thunk_FUN_14016c430(&pbStack_408);
                                                thunk_FUN_14016c430(auStack_348);
                                                thunk_FUN_14016c430(auStack_368);
                                                thunk_FUN_14016c430(&pppppppuStack_428);
                                                thunk_FUN_14016c430(&pppppppuStack_3c8);
                                                thunk_FUN_14016c430(&pbStack_448);
                                                thunk_FUN_140276ae0(auStack_2c8);
                                                thunk_FUN_14016c430(apppppppWStack_3e8);
                                                if (lpAttributeList !=
                                                    (LPPROC_THREAD_ATTRIBUTE_LIST)0x0) {
                                                  DeleteProcThreadAttributeList(lpAttributeList);
                                                  pvVar17 = GetProcessHeap();
                                                  HeapFree(pvVar17,0,lpAttributeList);
                                                }
                                                thunk_FUN_140166360(&pvStack_710);
                                                thunk_FUN_140166360(&pvStack_708);
                                                thunk_FUN_140166360(&pvStack_728);
                                                thunk_FUN_140166360(&pbStack_720);
                                                thunk_FUN_140166360(&puStack_730);
                                                thunk_FUN_140166360(&pvStack_738);
                                                thunk_FUN_140166360(&pvStack_740);
                                                thunk_FUN_14016c430(alStack_468);
                                                thunk_FUN_14016c430(&pppppppuStack_488);
                                                _Mtx_unlock(pbVar1);
                                                return 1;
                                              }
LAB_140705614:
                                              pppppppuStack_6e8 = (undefined8 *******)0x1416faca8;
                                              lStack_6e0 = 0x10;
                                              FUN_140702b60(*(
                                                  basic_ostream<char,std::char_traits<char>_> **)
                                                  (pbVar21 + 0x1a0));
                                            }
                                            if (param_11[2] != (undefined8 ******)0x0)
                                            goto LAB_140705660;
                                            uVar25 = 0x1b;
                                            pcVar22 = "terminal_bridge_unavailable";
                                          }
                                          thunk_FUN_14016cb60(param_11,pcVar22,uVar25);
                                        }
                                      }
LAB_140705660:
                                      thunk_FUN_140166360(&pbStack_6c8);
                                      thunk_FUN_140166360(apbStack_6f8);
                                    }
                                    thunk_FUN_14016c430(&pbStack_408);
                                    thunk_FUN_14016c430(auStack_348);
                                    thunk_FUN_14016c430(auStack_368);
                                    thunk_FUN_14016c430(&pppppppuStack_428);
                                    thunk_FUN_14016c430(&pppppppuStack_3c8);
                                    thunk_FUN_14016c430(&pbStack_448);
                                    thunk_FUN_140276ae0(auStack_2c8);
                                    thunk_FUN_14016c430(apppppppWStack_3e8);
                                    if (lpAttributeList != (LPPROC_THREAD_ATTRIBUTE_LIST)0x0) {
                                      DeleteProcThreadAttributeList(lpAttributeList);
                                      pvVar17 = GetProcessHeap();
                                      HeapFree(pvVar17,0,lpAttributeList);
                                    }
                                    thunk_FUN_140166360(&pvStack_710);
                                    thunk_FUN_140166360(&pvStack_708);
                                    thunk_FUN_140166360(&pvStack_728);
                                    thunk_FUN_140166360(&pbStack_720);
                                    thunk_FUN_140166360(&puStack_730);
                                    thunk_FUN_140166360(&pvStack_738);
                                    thunk_FUN_140166360(&pvStack_740);
                                    thunk_FUN_14016c430(alStack_468);
                                    thunk_FUN_14016c430(&pppppppuStack_488);
                                    goto LAB_1407058ef;
                                  }
                                  thunk_FUN_14016c430(&pbStack_408);
                                  thunk_FUN_14016c430(auStack_348);
                                  thunk_FUN_14016c430(auStack_368);
                                  thunk_FUN_14016c430(&pppppppuStack_428);
                                }
                                thunk_FUN_14016c430(&pppppppuStack_3c8);
                                thunk_FUN_14016c430(&pbStack_448);
                                thunk_FUN_140276ae0(auStack_2c8);
                                thunk_FUN_14016c430(apppppppWStack_3e8);
                                if (lpAttributeList != (LPPROC_THREAD_ATTRIBUTE_LIST)0x0) {
                                  DeleteProcThreadAttributeList(lpAttributeList);
                                  pvVar17 = GetProcessHeap();
                                  HeapFree(pvVar17,0,lpAttributeList);
                                }
                                thunk_FUN_140166360(&pvStack_710);
                                thunk_FUN_140166360(&pvStack_708);
                                thunk_FUN_140166360(&pvStack_728);
                                thunk_FUN_140166360(&pbStack_720);
                                thunk_FUN_140166360(&puStack_730);
                                thunk_FUN_140166360(&pvStack_738);
                                thunk_FUN_140166360(&pvStack_740);
                                thunk_FUN_14016c430(alStack_468);
                                thunk_FUN_14016c430(&pppppppuStack_488);
                                goto LAB_1407058ef;
                              }
                            }
                            else {
                              pbVar23 = pbVar21 + 0x2f8;
                              if ((basic_ostream<char,std::char_traits<char>_> *)&pppppppuStack_428
                                  != pbVar23) {
                                if ((basic_ostream<char,std::char_traits<char>_> *)0x7 <
                                    *(basic_ostream<char,std::char_traits<char>_> **)
                                     (pbVar21 + 0x310)) {
                                  pbVar23 = *(basic_ostream<char,std::char_traits<char>_> **)pbVar23
                                  ;
                                }
                                thunk_FUN_14016cd20(&pppppppuStack_428,pbVar23,
                                                    *(basic_ostream<char,std::char_traits<char>_> **
                                                     )(pbVar21 + 0x308));
                                if ((lStack_418 != 0) &&
                                   (*(basic_ostream<char,std::char_traits<char>_> **)
                                     (pbVar21 + 0x2c8) !=
                                    (basic_ostream<char,std::char_traits<char>_> *)0x0))
                                goto LAB_14070443f;
                              }
                              thunk_FUN_14016cb60(param_11,"terminal_mux_session_unavailable",0x20);
                            }
                            if (7 < uStack_410) {
                              thunk_FUN_14016a870(&pppppppuStack_428);
                            }
                            pppppppuStack_428 =
                                 (undefined8 *******)
                                 ((ulonglong)pppppppuStack_428 & 0xffffffffffff0000);
                            uStack_410 = 7;
                            lStack_418 = 0;
                            if (7 < uVar4) {
                              thunk_FUN_14016a870(&pppppppuStack_3c8);
                            }
                            if (7 < uStack_430) {
                              thunk_FUN_14016a870(&pbStack_448);
                            }
                          }
                          pbStack_448 = (basic_ostream<char,std::char_traits<char>_> *)
                                        ((ulonglong)pbStack_448 & 0xffffffffffff0000);
                          uStack_438 = 0;
                          uStack_430 = 7;
                          thunk_FUN_140276ae0(auStack_2c8);
                          thunk_FUN_14016c430(apppppppWStack_3e8);
                          goto joined_r0x000140704294;
                        }
                      }
LAB_1407057fb:
                      DeleteProcThreadAttributeList(lpAttributeList);
                      pvVar17 = GetProcessHeap();
                    }
                    HeapFree(pvVar17,0,lpAttributeList);
                  }
                }
LAB_140705819:
                thunk_FUN_140166360(&pvStack_710);
                thunk_FUN_140166360(&pvStack_708);
              }
            }
          }
        }
        thunk_FUN_140166360(&pvStack_728);
        thunk_FUN_140166360(&pbStack_720);
      }
      thunk_FUN_140166360(&puStack_730);
      thunk_FUN_140166360(&pvStack_738);
      thunk_FUN_140166360(&pvStack_740);
      if (7 < uStack_450) {
        thunk_FUN_14016a870(alStack_468,alStack_468[0]);
      }
    }
    if (7 < uStack_470) {
      thunk_FUN_14016a870(&pppppppuStack_488,pppppppuStack_488);
    }
  }
  else {
    p_Stack_698 = *(LPPROC_THREAD_ATTRIBUTE_LIST *)pbStack_328;
    DStack_690 = *(DWORD *)(pbStack_328 + 8);
    uStack_68c = *(undefined4 *)(pbStack_328 + 0xc);
    cVar9 = thunk_FUN_1402287e0(&p_Stack_698,&pppppppuStack_488);
    if (cVar9 != '\0') goto LAB_1407034c7;
    thunk_FUN_14016cb60(param_11,"terminal_display_name_invalid");
LAB_1407036d3:
    if (7 < uStack_470) {
      if (0xfff < uStack_470 * 2 + 2) {
        lVar16 = (longlong)pppppppuStack_488 - (longlong)pppppppuStack_488[-1];
joined_r0x000140703802:
        if (0x1f < lVar16 - 8U) {
                    /* WARNING: Subroutine does not return */
          _invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
        }
      }
LAB_14070371a:
      FUN_14005a335();
    }
  }
LAB_1407058b9:
  lStack_478 = 0;
  uStack_470 = 7;
  pppppppuStack_488 = (undefined8 *******)((ulonglong)pppppppuStack_488 & 0xffffffffffff0000);
LAB_1407058ef:
  _Mtx_unlock(pbVar1);
  return 0;
}

