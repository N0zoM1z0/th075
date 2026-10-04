#!/usr/bin/env python3
"""Replay the bounded R136 locale construction dependency graph."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_REG_EAX

ROOT = Path(__file__).resolve().parents[1]
ACCEPTED = {'0x0064C25F': ('__get_lc_time', 871), '0x0064C847': ('___init_numeric', 461), '0x0064CB20': ('___init_monetary', 575), '0x0064CD5F': ('___init_ctype', 490), '0x00642EE5': ('__expandlocale', 348), '0x00643041': ('__setlocale_set_cat', 655), '0x0064D853': ('___get_qualified_locale', 437), '0x00642D9D': ('___lc_lctostr', 78), '0x0064D114': ('_TranslateName', 96), '0x0064D778': ('_GetLcidFromLangCountry', 134), '0x0064D7FE': ('_GetLcidFromLanguage', 85), '0x0064D741': ('_GetLcidFromCountry', 55), '0x0064D174': ('_GetLcidFromDefault', 26), '0x0064D18E': ('_ProcessCodePage', 118), '0x00651B15': ('__stricmp', 105), '0x0064D33A': ('_GetPrimaryLen', 29), '0x0064D222': ('_crtGetLocaleInfoA@16', 227), '0x0064D45C': ('_LangCountryEnumProc@4', 538), '0x00651B7E': ('__strnicmp', 127), '0x0064D204': ('_TestDefaultCountry', 30), '0x0064D3EB': ('_TestDefaultLanguage', 113), '0x0064D676': ('_LanguageEnumProc@4', 203), '0x0064D357': ('_CountryEnumProc@4', 148)}
LEDGER_SIZES = {'0x0064C25F': 871, '0x0064C847': 461, '0x0064CB20': 575, '0x0064CD5F': 490, '0x00642EE5': 348, '0x00643041': 655, '0x0064D853': 437, '0x00642D9D': 78, '0x0064D114': 96, '0x0064D778': 134, '0x0064D7FE': 85, '0x0064D741': 55, '0x0064D174': 26, '0x0064D18E': 118, '0x00651B15': 105, '0x0064D33A': 29, '0x0064D222': 227, '0x0064D45C': 538, '0x00651B7E': 127, '0x0064D204': 30, '0x0064D3EB': 113, '0x0064D676': 203, '0x0064D357': 148}
AUXILIARIES = {'0x00642C9A': ('___init_dummy', 3), '0x0064CF9A': ('___init_collate', 3), '0x0064C756': ('___init_time', 95)}
LABELS = {}
STATE = {(1378176, '___lconv_intl', '0x0068E68C', 4), (1324526, '??_C@_0L@PLDJKEIL@english?9us?$AA@', '0x0066382C', 11), (1408564, '___mb_cur_max', '0x00670910', 12), (2326218, '??_C@_08BPBNCDIB@MM?1dd?1yy?$AA@', '0x00662584', 9), (1324526, '??_C@_0BE@BHDOHPMC@spanish?9puerto?5rico?$AA@', '0x006635E8', 20), (2326218, '??_C@_06JLEDEDGH@Monday?$AA@', '0x00662664', 7), (1324526, '??_C@_06FFOOPAJB@Basque?$AA@', '0x00663164', 7), (2326218, '??_C@_03NAGEINEP@Tue?$AA@', '0x00662684', 4), (2326218, '??_C@_04MIEPOIFP@July?$AA@', '0x006625CC', 5), (1324526, '??_C@_0BB@MNMBKDFE@english?9american?$AA@', '0x006638DC', 17), (1324526, '??_C@_0M@EFJANOAL@puerto?9rico?$AA@', '0x00663314', 12), (1324526, '??_C@_0BA@GBHHMIJI@spanish?9uruguay?$AA@', '0x006635D8', 16), (2326218, '??_C@_08EDHMEBNP@December?$AA@', '0x00662598', 9), (1324526, '??_C@_07HJLCKBG@holland?$AA@', '0x00663354', 8), (1324526, '??_C@_0BF@JMJMGNNF@english?9south?5africa?$AA@', '0x00663860', 21), (2326218, '??_C@_03JPJOFNIA@Nov?$AA@', '0x00662604', 4), (1324526, '??_C@_08PKBIPKE@Paraguay?$AA@', '0x0066305C', 9), (1324526, '??_C@_0BB@PDECHHHE@spanish?9honduras?$AA@', '0x00663664', 17), (1324526, '??_C@_0BC@LFEKMIFB@english?9caribbean?$AA@', '0x006638A0', 18), (1389094, '___lc_time_intl', '0x0068E688', 4), (1324526, '??_C@_0BB@DBEFDDME@chinese?9hongkong?$AA@', '0x0066393C', 17), (1324526, '??_C@_0BF@EALFLENP@portuguese?9brazilian?$AA@', '0x00663728', 21), (1324526, '??_C@_0N@FIELFKIJ@south?9africa?$AA@', '0x006632E0', 13), (2326218, '??_C@_03IDIOELNC@Fri?$AA@', '0x00662678', 4), (1324526, '??_C@_0N@KMOIDGGN@spanish?9peru?$AA@', '0x006635FC', 13), (1324526, '??_C@_0BD@FDKADDCP@chinese?9simplified?$AA@', '0x00663928', 19), (1324526, '??_C@_07FACOMELA@england?$AA@', '0x0066336C', 8), (1324526, '??_C@_06GODMCAND@French?$AA@', '0x00663198', 7), (2326218, '??_C@_08GNJGEPFN@February?$AA@', '0x006625EC', 9), (2326218, '??_C@_07JJNFCEND@October?$AA@', '0x006625B0', 8), (2326218, '??_C@_03ODNJBKGA@Mar?$AA@', '0x00662624', 4), (1398330, '___lconv_static_null', '0x0068E684', 1), (2326218, '??_C@_09BHHEALKD@September?$AA@', '0x006625B8', 10), (1324526, '??_C@_0P@MCPKNGFD@spanish?9panama?$AA@', '0x00663620', 15), (1324526, '??_C@_09IIIPPBDB@hong?9kong?$AA@', '0x00663348', 10), (1324526, '??_C@_07PFALJOGE@Spanish?$AA@', '0x0066315C', 8), (1324526, '??_C@_08IJLOKOLL@american?$AA@', '0x006639A8', 9), (1324526, '??_C@_09IDMFKCN@Venezuela?$AA@', '0x006630A0', 10), (1324526, '??_C@_0P@NDHFFKCA@united?9kingdom?$AA@', '0x006632B0', 15), (1444790, '__ctype_loc_style', '0x00660F98', 383), (1324526, '??_C@_08JHDOMCMI@pr?5china?$AA@', '0x0066332C', 9), (1324526, '??_C@_0P@CMPOCLM@french?9belgian?$AA@', '0x00663810', 15), (1410624, '___lc_id', '0x0068E6D8', 36), (1324526, '??_C@_0BB@PKCBKCPE@spanish?9colombia?$AA@', '0x006636E0', 17), (1324526, '??_C@_0BA@BEFEIGJJ@spanish?9bolivia?$AA@', '0x00663704', 16), (1324526, '??_C@_0O@KIDLNNBA@dutch?9belgian?$AA@', '0x006638F0', 14), (2326218, '??_C@_03BMAOKBAD@Oct?$AA@', '0x00662608', 4), (1444790, '??_C@_08EADHIDAD@LC_CTYPE?$AA@', '0x00661138', 9), (2326218, '??_C@_09DLIGFAKA@Wednesday?$AA@', '0x00662650', 10), (1324526, '??_C@_06DIAOLLEH@Mexico?$AA@', '0x00663154', 7), (1324526, '??_C@_0O@LEHGMHAG@great?5britain?$AA@', '0x0066335C', 14), (2326218, '??_C@_06LBBHFDDG@August?$AA@', '0x006625C4', 7), (1409460, '___lc_handle', '0x0068E6B4', 32), (1324526, '??_C@_0BC@MJJMPKCG@chinese?9singapore?$AA@', '0x00663914', 18), (1444790, '??_C@_01IDAFKMJL@_?$AA@', '0x00661160', 2), (1324526, '??_C@_0O@CNOMPGD@irish?9english?$AA@', '0x00663784', 14), (1324526, '??_C@_09PGNFPGME@Argentina?$AA@', '0x00663080', 10), (2326218, '??_C@_05DMJDNLEJ@April?$AA@', '0x006625DC', 6), (2326218, '??_C@_08HCHEGEOA@November?$AA@', '0x006625A4', 9), (1324526, '??_C@_07GHBIBIBP@Uruguay?$AA@', '0x00663068', 8), (1324526, '??_C@_0BB@DFMDPDGB@american?5english?$AA@', '0x00663994', 17), (1324526, '??_C@_0BC@KLHKFGDB@spanish?9guatemala?$AA@', '0x00663678', 18), (1324526, '??_C@_08PGOJKDAI@pr?9china?$AA@', '0x00663320', 9), (1324526, '??_C@_0BK@CKLIAGJB@english?9trinidad?5y?5tobago?$AA@', '0x00663844', 26), (1324526, '??_C@_05JMPCFJFJ@swiss?$AA@', '0x006635AC', 6), (1324526, '??_C@_03DFHEHBHG@ACP?$AA@', '0x006639B8', 4), (2326218, '??_C@_06JECMNKMI@Friday?$AA@', '0x0066263C', 7), (2326218, '??_C@_03LEOLGMJP@Apr?$AA@', '0x00662620', 4), (2326218, '??_C@_02DEDBPAFC@AM?$AA@', '0x00662594', 3), (1324526, '??_C@_08OAIPJDGI@canadian?$AA@', '0x00663960', 9), (1324526, '??_C@_07DHNMFMCI@chinese?$AA@', '0x00663950', 8), (1324526, '??_C@_02FGJGKGGD@us?$AA@', '0x006635A4', 3), (1324526, '??_C@_05BBJOBLGB@china?$AA@', '0x0066337C', 6), (1324526, '??_C@_07NEKHPBCG@English?$AA@', '0x00663134', 8), (1324526, '??_C@_0L@BOCNDGON@Luxembourg?$AA@', '0x006630D8', 11), (1324526, '??_C@_0O@EAJFJDFG@italian?9swiss?$AA@', '0x00663774', 14), (1324526, '??_C@_0BG@CCEBNPGH@Spanish?5?9?5Modern?5Sort?$AA@', '0x00663110', 22), (1324526, '??_C@_0BC@IHOHGAIL@spanish?9nicaragua?$AA@', '0x00663630', 18), (1324526, '??_C@_03BMMIADDJ@chh?$AA@', '0x0066395C', 4), (2326218, '??_C@_08JCCMCCIL@HH?3mm?3ss?$AA@', '0x00662564', 9), (2326218, '??_C@_03LBGABGKK@Jul?$AA@', '0x00662614', 4), (1324526, '??_C@_0BC@EMECMPD@spanish?9argentina?$AA@', '0x00663714', 18), (1324526, '??_C@_05CBHOCCK@Spain?$AA@', '0x006631B0', 6), (1324526, '??_C@_0BC@JACMHNBP@german?9luxembourg?$AA@', '0x006637A4', 18), (1324526, '??_C@_06DGHNDJFJ@Sweden?$AA@', '0x0066316C', 7), (1324526, '??_C@_0BL@PLMGIMOO@spanish?9dominican?5republic?$AA@', '0x006636B0', 27), (1324526, '??_C@_06COBCPIFO@France?$AA@', '0x00663190', 7), (1444790, '___lc_category', '0x006700B8', 72), (1324526, '??_C@_07HBPMNPNJ@belgian?$AA@', '0x0066396C', 8), (1324526, '??_C@_0M@GHHDJOK@english?9usa?$AA@', '0x00663820', 12), (1324526, '??_C@_07LIIIOFOA@Belgium?$AA@', '0x0066314C', 8), (1324526, '??_C@_0BC@DJFJJCK@french?9luxembourg?$AA@', '0x006637EC', 18), (1444790, '??_C@_0L@DLHIECNL@LC_NUMERIC?$AA@', '0x00661120', 11), (1324526, '??_C@_09JHBBDDIA@Icelandic?$AA@', '0x00663184', 10), (1308928, '__pctype', '0x006708C0', 8), (1409460, '___lc_clike', '0x00670900', 4), (1324526, '??_C@_0N@LPINDNDB@South?5Africa?$AA@', '0x006630C0', 13), (1324526, '??_C@_09EFGJAPAD@Australia?$AA@', '0x00663128', 10), (1324526, '??_C@_0BE@JBKABBMH@chinese?9traditional?$AA@', '0x00663900', 20), (2326218, '??_C@_03HJBDCHOM@Feb?$AA@', '0x00662628', 4), (2326218, '___lc_time_curr', '0x00670800', 4), (1324526, '??_C@_0BB@MEIMBEDG@american?9english?$AA@', '0x00663980', 17), (1324526, '??_C@_0BA@ONHGJCLH@english?9jamaica?$AA@', '0x00663884', 16), (1324526, '??_C@_06FKAPCJLB@slovak?$AA@', '0x0066330C', 7), (1324526, '??_C@_02JHCHFBLL@nz?$AA@', '0x00663338', 3), (1324526, '??_C@_0M@OLDPFKHI@english?9can?$AA@', '0x006638B4', 12), (1444790, '__clocalestr', '0x0066FF20', 403), (1324526, '??_C@_0N@GCAEPEBK@french?9swiss?$AA@', '0x006637DC', 13), (1324526, '??_C@_0BC@PKCNIABK@spanish?9venezuela?$AA@', '0x006635C4', 18), (2326218, '??_C@_03MHOMLAJA@Wed?$AA@', '0x00662680', 4), (2326218, '??_C@_07BAAGCFCM@Tuesday?$AA@', '0x0066265C', 8), (2326218, '??_C@_08INBOOONO@Saturday?$AA@', '0x00662630', 9), (1324526, '??_C@_0L@OEKOPBEL@australian?$AA@', '0x00663974', 11), (1324526, '??_C@_0L@HJCCDMNC@english?9uk?$AA@', '0x00663838', 11), (2326218, '??_C@_06OOPIFAJ@Sunday?$AA@', '0x0066266C', 7), (1324526, '??_C@_06EDDDIONA@German?$AA@', '0x00663144', 7), (1324526, '??_C@_09FJGLIMAG@Guatemala?$AA@', '0x006630FC', 10), (1324526, '??_C@_0M@OPNDHCMC@south?5korea?$AA@', '0x006632F0', 12), (1324526, '??_C@_06BLJPEOBG@Panama?$AA@', '0x006630D0', 7), (1324526, '??_C@_04IALPBJF@Peru?$AA@', '0x0066308C', 5), (1324526, '??_C@_0L@CONEHKA@Costa?5Rica?$AA@', '0x006630E4', 11), (1324526, '??_C@_0BD@DNEJOGOK@Dominican?5Republic?$AA@', '0x006630AC', 19), (1324526, '??_C@_0O@MCBIJGNE@spanish?9chile?$AA@', '0x006636F4', 14), (1324526, '??_C@_0BD@HLGDNMHB@spanish?9costa?5rica?$AA@', '0x006636CC', 19), (2326218, '??_C@_03GGCAPAJC@Sep?$AA@', '0x0066260C', 4), (1324526, '??_C@_07LKIIOGFH@Austria?$AA@', '0x0066313C', 8), (1324526, '??_C@_07MHIPBHMG@america?$AA@', '0x0066338C', 8), (1324526, '??_C@_0BA@HKKBIBKL@german?9austrian?$AA@', '0x006637CC', 16), (1324526, '??_C@_0N@EDHBGCKG@german?9swiss?$AA@', '0x00663794', 13), (1324526, '??_C@_0N@MDEOEPFI@south?5africa?$AA@', '0x006632FC', 13), (1663884, '__umaskval', '0x0068E2E4', 72), (1324526, '??_C@_0L@DKIIFDFD@english?9nz?$AA@', '0x00663878', 11), (1324526, '___rglangidNotDefault', '0x006631D4', 20), (2326218, '??_C@_02CJNFDJBF@PM?$AA@', '0x00662590', 3), (1324526, '??_C@_0O@FMJNFNKE@united?9states?$AA@', '0x006632A0', 14), (1444790, '??_C@_0L@KFJHEKIK@LC_COLLATE?$AA@', '0x00661144', 11), (1324526, '??_C@_07MFHPMOED@Finland?$AA@', '0x006631A0', 8), (1324526, '??_C@_03KIALPMKC@usa?$AA@', '0x006635A0', 4), (1324526, '??_C@_03NFKLAGEF@OCP?$AA@', '0x006639B4', 4), (2326218, '??_C@_0BE@CKGJFCPC@dddd?0?5MMMM?5dd?0?5yyyy?$AA@', '0x00662570', 20), (1444790, '??_C@_01LFCBOECM@?4?$AA@', '0x0066115C', 2), (1324526, '??_C@_0BC@NFIEMBLL@Norwegian?9Nynorsk?$AA@', '0x006639BC', 18), (1324526, '??_C@_0BA@FCOKFPFC@spanish?9ecuador?$AA@', '0x006636A0', 16), (1444790, '??_C@_0M@MIENIKLA@LC_MONETARY?$AA@', '0x0066112C', 12), (2326218, '??_C@_03JIHJHPIE@Jan?$AA@', '0x0066262C', 4), (1324526, '___rg_country', '0x006631E8', 184), (1398330, '___lconv_static_decimal', '0x006708C8', 56), (1444790, '?cacheid@?1??_expandlocale@@9@9', '0x0068E2D8', 12), (2326218, '??_C@_04CNLMGBGM@June?$AA@', '0x006625D4', 5), (1324526, '??_C@_05HBNKAPDN@Chile?$AA@', '0x00663070', 6), (1324526, '??_C@_0BA@HLOCPIOD@swedish?9finland?$AA@', '0x006635B4', 16), (1236214, '___security_cookie', '0x0066FE30', 4), (1444790, '??_C@_00CNPNBAHC@?$AA@', '0x006609AB', 1), (1324526, '??_C@_0M@HJBGHOPO@english?9ire?$AA@', '0x00663894', 12), (1324526, '??_C@_0BA@NNCEDFIC@french?9canadian?$AA@', '0x00663800', 16), (2326218, '??_C@_03MKABNOCG@Dec?$AA@', '0x00662600', 4), (1444790, '??_C@_06NEFDFEKB@LC_ALL?$AA@', '0x00661150', 7), (2326218, '??_C@_03FEFJNEK@Sat?$AA@', '0x00662674', 4), (2326218, '___lc_time_c', '0x00670808', 184), (1324526, '??_C@_0BE@HBGMGFEG@german?9lichtenstein?$AA@', '0x006637B8', 20), (1324526, '___rg_language', '0x00663398', 520), (2326218, '??_C@_03IDFGHECI@Jun?$AA@', '0x00662618', 4), (2326218, '??_C@_05HPCKOFNC@March?$AA@', '0x006625E4', 6), (1324526, '??_C@_03FNDDCHI@chi?$AA@', '0x00663958', 4), (1324526, '??_C@_08IJPLNLKH@Colombia?$AA@', '0x00663094', 9), (1324526, '??_C@_07NCOIHDGC@Iceland?$AA@', '0x0066317C', 8), (2326218, '??_C@_03PDAGKDH@Mon?$AA@', '0x00662688', 4), (1324526, '??_C@_07MCEAMKOD@Finnish?$AA@', '0x006631A8', 8), (1324526, '_iLcidState', '0x0068E690', 36), (1324526, '??_C@_0P@OMDEHBMP@english?9belize?$AA@', '0x006638C0', 15), (2326218, '??_C@_03IFJFEIGA@Aug?$AA@', '0x00662610', 4), (2326218, '??_C@_08HACCIKIA@Thursday?$AA@', '0x00662644', 9), (1324526, '??_C@_0M@KFHFPFED@english?9aus?$AA@', '0x006638D0', 12), (2326218, '??_C@_03CNMDKL@May?$AA@', '0x0066261C', 4), (1324526, '??_C@_0BB@HMHLPGPH@spanish?9paraguay?$AA@', '0x0066360C', 17), (1324526, '??_C@_02NEINDODK@uk?$AA@', '0x006635A8', 3), (1324526, '??_C@_06ECHIPDMK@Canada?$AA@', '0x00663108', 7), (1324526, '??_C@_0BE@MFOOKJAI@spanish?9el?5salvador?$AA@', '0x0066368C', 20), (1324526, '??_C@_07OBINPKFN@Swedish?$AA@', '0x00663174', 8), (1324526, '??_C@_07GPKPHICP@britain?$AA@', '0x00663384', 8), (1324526, '??_C@_07FEIFIPNF@Ecuador?$AA@', '0x00663078', 8), (1324526, '??_C@_0P@KLMJDNFJ@spanish?9modern?$AA@', '0x00663644', 15), (1324526, '??_C@_0BB@HMACDDCK@norwegian?9bokmal?$AA@', '0x00663754', 17), (1324526, '??_C@_05JIHCEICB@czech?$AA@', '0x00663374', 6), (1324526, '??_C@_0BL@GIOEGDHB@Spanish?5?9?5Traditional?5Sort?$AA@', '0x006631B8', 27), (1324526, '___rgLocInfo', '0x00662BB8', 1188), (1444790, '??_C@_07LCBHPJJN@LC_TIME?$AA@', '0x00661118', 8), (1324526, '??_C@_0M@IOAEBDAC@south?9korea?$AA@', '0x006632D4', 12), (1308928, '___newctype', '0x006626B0', 1284), (2326218, '??_C@_07CGJPFGJA@January?$AA@', '0x006625F8', 8), (2326218, '??_C@_03KOEHGMDN@Sun?$AA@', '0x0066268C', 4), (1324526, '??_C@_0M@LINHDHKP@new?9zealand?$AA@', '0x0066333C', 12), (1324526, '??_C@_0BC@HHDADLGF@trinidad?5?$CG?5tobago?$AA@', '0x006632C0', 18), (1324526, '??_C@_0BA@BPAPGBCM@spanish?9mexican?$AA@', '0x00663654', 16), (1324526, '??_C@_0M@KGBPELAM@Switzerland?$AA@', '0x006630F0', 12), (2326218, '??_C@_03IOFIKPDN@Thu?$AA@', '0x0066267C', 4), (1324526, '??_C@_0BC@HBLEBLNN@norwegian?9nynorsk?$AA@', '0x00663740', 18), (1324526, '??_C@_09BAFFPPHE@norwegian?$AA@', '0x00663768', 10)}
LAYOUT_OBJECTS = [{'symbol': '_LocaleConstructionLayoutProbe', 'offset': 0, 'size': 340, 'storage_span': 340, 'values': [4, 4, 2, 4, 4, 4, 6, 0, 2, 4, 144, 0, 64, 128, 64, 64, 16, 131, 12, 0, 4, 8, 72, 0, 1, 2, 3, 4, 5, 0, 5, 8, 40, 8, 4, 44, 4, 12, 16, 20, 24, 28, 36, 48, 8, 28, 40, 47, 184, 28, 56, 104, 152, 160, 164, 168, 172, 176, 180, 84, 20, 0, 4, 6, 12, 5, 257, 127, 768, 254, 32768, 1, 1, 2, 4097, 4098, 3, 7, 11, 4100, 4, 1, 0, 256, 127]}]
LAYOUT_HEADERS = {'crt/src/setlocal.h', 'PlatformSDK/Include/WinBase.h', 'crt/src/mtdll.h', 'crt/src/limits.h', 'crt/src/locale.h', 'PlatformSDK/Include/WinNT.h', 'PlatformSDK/Include/WinNls.h', 'crt/src/ctype.h'}
CALL_CONTROLS = [{'coff_symbol': '_LocaleEnumCallbackControl@4', 'size': 45, 'source_sha256': '4d26c84ae03f15b938ffcff41acf771504a78c01e4e31e01af3cdf047fdae070', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x0000002A', 'cleanup': 4}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x00000004', 'mnemonic': 'cmp', 'operands': 'dword ptr [ebp + 8], 0'}, {'site': '0x00000008', 'mnemonic': 'je', 'operands': '0x1d'}, {'site': '0x0000000A', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x0000000D', 'mnemonic': 'movsx', 'operands': 'ecx, byte ptr [eax]'}, {'site': '0x00000010', 'mnemonic': 'test', 'operands': 'ecx, ecx'}, {'site': '0x00000012', 'mnemonic': 'je', 'operands': '0x1d'}, {'site': '0x00000014', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], 1'}, {'site': '0x0000001B', 'mnemonic': 'jmp', 'operands': '0x24'}, {'site': '0x0000001D', 'mnemonic': 'mov', 'operands': 'dword ptr [ebp - 4], 0'}, {'site': '0x00000024', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp - 4]'}, {'site': '0x00000027', 'mnemonic': 'mov', 'operands': 'esp, ebp'}, {'site': '0x00000029', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x0000002A', 'mnemonic': 'ret', 'operands': '4'}]}, {'coff_symbol': '_LocaleEnumRegisterControl', 'size': 17, 'source_sha256': 'b63eb9c7344b031580221c9a8d71cfbb61e8d4913c975c9d4a37f1b9af32e521', 'relocation_metadata': [{'offset': 11, 'type': 'DIR32', 'symbol': '__imp__EnumSystemLocalesA@8', 'addend': 0, 'local_symbol_offset': None}], 'body_facts': {'returns': [{'site': '0x00000010', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'push', 'operands': '1'}, {'site': '0x00000005', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 8]'}, {'site': '0x00000008', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000009', 'mnemonic': 'call', 'operands': 'dword ptr [0]'}, {'site': '0x0000000F', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000010', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_LocaleCategoryInitControl', 'size': 8, 'source_sha256': 'ed838c74bda743a052d4f2a1d3508b800e0b8849758020f961f744c414b44341', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000007', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000006', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000007', 'mnemonic': 'ret', 'operands': ''}]}, {'coff_symbol': '_LocaleQuerySlotControl', 'size': 24, 'source_sha256': 'b7fc607f9908805ec7f6931b7b458f9a228eb12c1ee10b20ddaba624b363ce97', 'relocation_metadata': [], 'body_facts': {'returns': [{'site': '0x00000017', 'cleanup': 0}], 'direct_calls': [], 'vtable_writes': []}, 'instructions': [{'site': '0x00000000', 'mnemonic': 'push', 'operands': 'ebp'}, {'site': '0x00000001', 'mnemonic': 'mov', 'operands': 'ebp, esp'}, {'site': '0x00000003', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0x18]'}, {'site': '0x00000006', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000007', 'mnemonic': 'mov', 'operands': 'ecx, dword ptr [ebp + 0x14]'}, {'site': '0x0000000A', 'mnemonic': 'push', 'operands': 'ecx'}, {'site': '0x0000000B', 'mnemonic': 'mov', 'operands': 'edx, dword ptr [ebp + 0x10]'}, {'site': '0x0000000E', 'mnemonic': 'push', 'operands': 'edx'}, {'site': '0x0000000F', 'mnemonic': 'mov', 'operands': 'eax, dword ptr [ebp + 0xc]'}, {'site': '0x00000012', 'mnemonic': 'push', 'operands': 'eax'}, {'site': '0x00000013', 'mnemonic': 'call', 'operands': 'dword ptr [ebp + 8]'}, {'site': '0x00000016', 'mnemonic': 'pop', 'operands': 'ebp'}, {'site': '0x00000017', 'mnemonic': 'ret', 'operands': ''}]}]
VENDOR_SOURCES = {'crt/src/setlocal.c', 'crt/src/strnicmp.c', 'crt/src/stricmp.c', 'crt/src/inittime.c', 'crt/src/getqloc.c', 'crt/src/initmon.c', 'crt/src/initcoll.c', 'crt/src/initctyp.c', 'crt/src/intel/memcpy.asm', 'crt/src/initnum.c'}
CONFIDENCE = 'complete-vendor-locale-construction-code-data-callback-api-abi-provenance'
LABEL_CONFIDENCE = 'unused-no-new-interior-locale-labels'

ANCHORS = [('0x006519EE', '___getlocaleinfo', 295, 1375360, 'R135'), ('0x00642A61', '_free', 113, 794604, 'R120'), ('0x00644343', '_calloc', 187, 788256, 'R120'), ('0x00644331', '_malloc', 18, 816374, 'R120'), ('0x0064C7E8', '___free_lconv_num', 95, 1383738, 'R122'), ('0x0064CA47', '___free_lconv_mon', 217, 1378176, 'R122'), ('0x0064DA08', '___crtGetStringTypeA', 442, 1276190, 'R123'), ('0x00640F20', '_memcpy', 829, 2159808, 'R025'), ('0x00640611', '@__security_check_cookie@4', 14, 1230768, 'R120'), ('0x00640620', '_strlen', 139, 2200788, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x006416B0', '_strcmp', 136, 2192172, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00642CC1', '___lc_strtolc', 220, 1444790, 'R099'), ('0x0064CFF0', '_strncpy', 292, 2207814, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00641B80', '_strcpy', 7, 2186124, 'R116'), ('0x00641F00', '_memcmp', 184, 2169288, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00651C3B', '__itoa', 42, 232636, 'R007'), ('0x00642C9D', '__strcats', 36, 1444790, 'R007'), ('0x00642619', '_atol', 136, 157246, 'R123'), ('0x00646196', '__getptd', 113, 1724384, 'R120'), ('0x00642DEB', '___updatetlocinfo', 59, 1444790, 'R123'), ('0x006519A0', '___ascii_stricmp', 78, 2197148, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064F31D', '___tolower_mt', 200, 192908, 'R124'), ('0x0064D305', '_LcidFromHexString', 53, 1324526, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x00653DA0', '___ascii_strnicmp', 97, 2213628, 'R006; docs/ORIGIN_REVIEW.md; config/runtime-origin-evidence.csv; complete archive identity and CFG'), ('0x0064C5C6', '___free_lc_time', 400, 1389094, 'R122')]
IO_PROTOCOL = {'category_size': 12, 'category_entries': 6, 'category_array_size': 72, 'locale_id_size': 6, 'locale_strings_size': 144, 'locale_cache_capacity': 131, 'compatibility_size': 8, 'compatibility_entries': 5, 'compatibility_size_total': 40, 'lconv_size': 48, 'time_locale_size': 184, 'time_refcount_offset': 180, 'locale_name_size': 8, 'locale_info_size': 44, 'country_entries': 23, 'language_entries': 65, 'fallback_locale_entries': 27, 'nondefault_langids': 10, 'thread_locale_size': 84, 'cpinfo_size': 20, 'cpinfo_leadbyte_offset': 6, 'cpinfo_leadbyte_size': 12, 'classification_entries': 257, 'classification_offset': 127, 'classification_allocation': 768, 'classification_copy_bytes': 254, 'classification_style_entries': 128, 'classification_style_bytes': 256, 'classification_source_chars': 127, 'category_style_carrier': 383, 'ctype_leadbyte_flag': 32768, 'enum_installed_flag': 1, 'nt_platform': 2, 'query_callee_cleanup': 16, 'enum_callback_cleanup': 4}

CODE_SIZES = {'0x0064C25F': 871, '0x0064C847': 461, '0x0064CB20': 575, '0x0064CD5F': 490, '0x00642EE5': 348, '0x00643041': 655, '0x0064D853': 437, '0x00642D9D': 78, '0x0064D114': 96, '0x0064D778': 134, '0x0064D7FE': 85, '0x0064D741': 55, '0x0064D174': 26, '0x0064D18E': 118, '0x00651B15': 105, '0x0064D33A': 29, '0x0064D222': 227, '0x0064D45C': 538, '0x00651B7E': 127, '0x0064D204': 30, '0x0064D3EB': 113, '0x0064D676': 203, '0x0064D357': 148}
LOCALE_OBJECTS = []
LOCALE_HEADERS = set()
EMBEDDED_TABLES = []
RUNTIME_DISPATCH = {}

SEH_SCOPES = []
LOCALE_CALL_CONTROLS = []

COMMON_GLOBALS = [{'member_offset': 1378176, 'member': 'build\\intel\\mt_obj\\initmon.obj', 'member_sha256': '883d0635b5d21a0dc1a68fc1860aa5b9d453f296d7a4972b04f3b06ca1aec4bf', 'symbol': '___lconv_intl_refcount', 'target_address': '0x0068FA50', 'size': 4, 'source_definition': {'symbol': '___lconv_intl_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1383738, 'member': 'build\\intel\\mt_obj\\initnum.obj', 'member_sha256': '2795eb04ba1543675fe995c81465fd3ec482144c083b014ce0a22caad65bbca2', 'symbol': '___lconv_num_refcount', 'target_address': '0x0068FA54', 'size': 4, 'source_definition': {'symbol': '___lconv_num_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1378176, 'member': 'build\\intel\\mt_obj\\initmon.obj', 'member_sha256': '883d0635b5d21a0dc1a68fc1860aa5b9d453f296d7a4972b04f3b06ca1aec4bf', 'symbol': '___lconv_mon_refcount', 'target_address': '0x0068FA4C', 'size': 4, 'source_definition': {'symbol': '___lconv_mon_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1369054, 'member': 'build\\intel\\mt_obj\\initctyp.obj', 'member_sha256': '7abd883fbeb516b8f64bdda31e272d2400083c994ac7c299f221bc92b76103ac', 'symbol': '___ctype1_refcount', 'target_address': '0x0068FA48', 'size': 4, 'source_definition': {'symbol': '___ctype1_refcount', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}, {'member_offset': 1369054, 'member': 'build\\intel\\mt_obj\\initctyp.obj', 'member_sha256': '7abd883fbeb516b8f64bdda31e272d2400083c994ac7c299f221bc92b76103ac', 'symbol': '___ctype1', 'target_address': '0x0068FA44', 'size': 4, 'source_definition': {'symbol': '___ctype1', 'offset': 4, 'section': 0, 'type': 0, 'storage': 2}, 'zero_fill_region': {'section': '.data', 'base': '0x0066C000', 'raw_size': 24576, 'virtual_size': 146376, 'flags': '0xC0000040'}}]
MEMCPY_REGIONS = [{'offset': 0, 'size': 100}, {'offset': 112, 'size': 112}, {'offset': 256, 'size': 76}, {'offset': 348, 'size': 148}, {'offset': 508, 'size': 128}, {'offset': 668, 'size': 76}, {'offset': 760, 'size': 69}]
MEMCPY_TABLES = [{'symbol': 'LeadUpVec', 'offset': 100, 'size': 12, 'source_definition': {'symbol': 'LeadUpVec', 'offset': 100, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 100, 'symbol': 'LeadUp1', 'target_address': '0x00640F90', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 112, 'source_definition': {'symbol': 'LeadUp1', 'offset': 112, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 104, 'symbol': 'LeadUp2', 'target_address': '0x00640FBC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 156, 'source_definition': {'symbol': 'LeadUp2', 'offset': 156, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 108, 'symbol': 'LeadUp3', 'target_address': '0x00640FE0', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 192, 'source_definition': {'symbol': 'LeadUp3', 'offset': 192, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'UnwindUpVec', 'offset': 224, 'size': 32, 'source_definition': {'symbol': 'UnwindUpVec', 'offset': 224, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 224, 'symbol': 'UnwindUp0', 'target_address': '0x00641063', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 323, 'source_definition': {'symbol': 'UnwindUp0', 'offset': 323, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 228, 'symbol': 'UnwindUp1', 'target_address': '0x00641050', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 304, 'source_definition': {'symbol': 'UnwindUp1', 'offset': 304, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 232, 'symbol': 'UnwindUp2', 'target_address': '0x00641048', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 296, 'source_definition': {'symbol': 'UnwindUp2', 'offset': 296, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 236, 'symbol': 'UnwindUp3', 'target_address': '0x00641040', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 288, 'source_definition': {'symbol': 'UnwindUp3', 'offset': 288, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 240, 'symbol': 'UnwindUp4', 'target_address': '0x00641038', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 280, 'source_definition': {'symbol': 'UnwindUp4', 'offset': 280, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 244, 'symbol': 'UnwindUp5', 'target_address': '0x00641030', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 272, 'source_definition': {'symbol': 'UnwindUp5', 'offset': 272, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 248, 'symbol': 'UnwindUp6', 'target_address': '0x00641028', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 264, 'source_definition': {'symbol': 'UnwindUp6', 'offset': 264, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 252, 'symbol': 'UnwindUp7', 'target_address': '0x00641020', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 256, 'source_definition': {'symbol': 'UnwindUp7', 'offset': 256, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'TrailUpVec', 'offset': 332, 'size': 16, 'source_definition': {'symbol': 'TrailUpVec', 'offset': 332, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 332, 'symbol': 'TrailUp0', 'target_address': '0x0064107C', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 348, 'source_definition': {'symbol': 'TrailUp0', 'offset': 348, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 336, 'symbol': 'TrailUp1', 'target_address': '0x00641084', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 356, 'source_definition': {'symbol': 'TrailUp1', 'offset': 356, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 340, 'symbol': 'TrailUp2', 'target_address': '0x00641090', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 368, 'source_definition': {'symbol': 'TrailUp2', 'offset': 368, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 344, 'symbol': 'TrailUp3', 'target_address': '0x006410A4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 388, 'source_definition': {'symbol': 'TrailUp3', 'offset': 388, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'LeadDownVec', 'offset': 496, 'size': 12, 'source_definition': {'symbol': 'LeadDownVec', 'offset': 496, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 496, 'symbol': 'LeadDown1', 'target_address': '0x0064111C', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 508, 'source_definition': {'symbol': 'LeadDown1', 'offset': 508, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 500, 'symbol': 'LeadDown2', 'target_address': '0x00641140', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 544, 'source_definition': {'symbol': 'LeadDown2', 'offset': 544, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 504, 'symbol': 'LeadDown3', 'target_address': '0x00641168', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 584, 'source_definition': {'symbol': 'LeadDown3', 'offset': 584, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'UnwindDownVec', 'offset': 636, 'size': 32, 'source_definition': {'symbol': 'UnwindDownVec', 'offset': 636, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 636, 'symbol': 'UnwindDown7', 'target_address': '0x006411BC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 668, 'source_definition': {'symbol': 'UnwindDown7', 'offset': 668, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 640, 'symbol': 'UnwindDown6', 'target_address': '0x006411C4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 676, 'source_definition': {'symbol': 'UnwindDown6', 'offset': 676, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 644, 'symbol': 'UnwindDown5', 'target_address': '0x006411CC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 684, 'source_definition': {'symbol': 'UnwindDown5', 'offset': 684, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 648, 'symbol': 'UnwindDown4', 'target_address': '0x006411D4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 692, 'source_definition': {'symbol': 'UnwindDown4', 'offset': 692, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 652, 'symbol': 'UnwindDown3', 'target_address': '0x006411DC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 700, 'source_definition': {'symbol': 'UnwindDown3', 'offset': 700, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 656, 'symbol': 'UnwindDown2', 'target_address': '0x006411E4', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 708, 'source_definition': {'symbol': 'UnwindDown2', 'offset': 708, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 660, 'symbol': 'UnwindDown1', 'target_address': '0x006411EC', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 716, 'source_definition': {'symbol': 'UnwindDown1', 'offset': 716, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 664, 'symbol': 'UnwindDown0', 'target_address': '0x006411FF', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 735, 'source_definition': {'symbol': 'UnwindDown0', 'offset': 735, 'section': 1, 'type': 0, 'storage': 6}}}]}, {'symbol': 'TrailDownVec', 'offset': 744, 'size': 16, 'source_definition': {'symbol': 'TrailDownVec', 'offset': 744, 'section': 1, 'type': 0, 'storage': 3}, 'entries': [{'offset': 744, 'symbol': 'TrailDown0', 'target_address': '0x00641218', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 760, 'source_definition': {'symbol': 'TrailDown0', 'offset': 760, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 748, 'symbol': 'TrailDown1', 'target_address': '0x00641220', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 768, 'source_definition': {'symbol': 'TrailDown1', 'offset': 768, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 752, 'symbol': 'TrailDown2', 'target_address': '0x00641230', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 784, 'source_definition': {'symbol': 'TrailDown2', 'offset': 784, 'section': 1, 'type': 0, 'storage': 6}}}, {'offset': 756, 'symbol': 'TrailDown3', 'target_address': '0x00641244', 'code_entry': {'owner': '0x00640F20', 'source_member_offset': 2159808, 'source_offset': 804, 'source_definition': {'symbol': 'TrailDown3', 'offset': 804, 'section': 1, 'type': 0, 'storage': 6}}}]}]
CATEGORY_DISPATCH = {'address': '0x006700B8', 'size': 72, 'stride': 12, 'entries': [{'index': 0, 'offset': 8, 'symbol': '___init_dummy', 'target_address': '0x00642C9A', 'code_entry': {'owner': '0x00642C9A', 'source_member_offset': 1444790, 'source_offset': 0, 'source_definition': {'symbol': '___init_dummy', 'offset': 0, 'section': 24, 'type': 32, 'storage': 2}}}, {'index': 1, 'offset': 20, 'symbol': '___init_collate', 'target_address': '0x0064CF9A', 'code_entry': {'owner': '0x0064CF9A', 'source_member_offset': 1363154, 'source_offset': 0, 'source_definition': {'symbol': '___init_collate', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'index': 2, 'offset': 32, 'symbol': '___init_ctype', 'target_address': '0x0064CD5F', 'code_entry': {'owner': '0x0064CD5F', 'source_member_offset': 1369054, 'source_offset': 0, 'source_definition': {'symbol': '___init_ctype', 'offset': 0, 'section': 2, 'type': 32, 'storage': 2}}}, {'index': 3, 'offset': 44, 'symbol': '___init_monetary', 'target_address': '0x0064CB20', 'code_entry': {'owner': '0x0064CB20', 'source_member_offset': 1378176, 'source_offset': 0, 'source_definition': {'symbol': '___init_monetary', 'offset': 0, 'section': 9, 'type': 32, 'storage': 2}}}, {'index': 4, 'offset': 56, 'symbol': '___init_numeric', 'target_address': '0x0064C847', 'code_entry': {'owner': '0x0064C847', 'source_member_offset': 1383738, 'source_offset': 0, 'source_definition': {'symbol': '___init_numeric', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}, {'index': 5, 'offset': 68, 'symbol': '___init_time', 'target_address': '0x0064C756', 'code_entry': {'owner': '0x0064C756', 'source_member_offset': 1389094, 'source_offset': 0, 'source_definition': {'symbol': '___init_time', 'offset': 0, 'section': 8, 'type': 32, 'storage': 2}}}], 'call_site': '0x0064326A', 'operand': 'dword ptr [ebx + 0x6700c0]', 'basis': 'Complete six-record defining source table; source-local category helper invokes selected initializer; LC_ALL dummy is source-defined and documented unused; current runtime categories unknown'}
CALLBACK_REGISTRATIONS = [{'caller': '0x0064D778', 'callback': '0x0064D45C', 'field_offset': 97, 'push_site': '0x0064D7D8', 'flag_site': '0x0064D7D6', 'flag': 1, 'call_site': '0x0064D7DD', 'import_name': 'EnumSystemLocalesA', 'iat': '0x00657118', 'code_entry': {'owner': '0x0064D45C', 'source_member_offset': 1324526, 'source_offset': 0, 'source_definition': {'symbol': '_LangCountryEnumProc@4', 'offset': 0, 'section': 152, 'type': 32, 'storage': 3}}}, {'caller': '0x0064D7FE', 'callback': '0x0064D676', 'field_offset': 58, 'push_site': '0x0064D837', 'flag_site': '0x0064D835', 'flag': 1, 'call_site': '0x0064D83C', 'import_name': 'EnumSystemLocalesA', 'iat': '0x00657118', 'code_entry': {'owner': '0x0064D676', 'source_member_offset': 1324526, 'source_offset': 0, 'source_definition': {'symbol': '_LanguageEnumProc@4', 'offset': 0, 'section': 154, 'type': 32, 'storage': 3}}}, {'caller': '0x0064D741', 'callback': '0x0064D357', 'field_offset': 23, 'push_site': '0x0064D757', 'flag_site': '0x0064D754', 'flag': 1, 'call_site': '0x0064D761', 'import_name': 'EnumSystemLocalesA', 'iat': '0x00657118', 'code_entry': {'owner': '0x0064D357', 'source_member_offset': 1324526, 'source_offset': 0, 'source_definition': {'symbol': '_CountryEnumProc@4', 'offset': 0, 'section': 148, 'type': 32, 'storage': 3}}}]
QUERY_DISPATCH = {'state_symbol': '_pfnGetLocaleInfoA', 'address': '0x0068E6B0', 'carrier_symbol': '_iLcidState', 'carrier_address': '0x0068E690', 'carrier_size': 36, 'offset': 32, 'initial_value': 0, 'owner': '0x0064D853', 'platform_address': '0x0068E2E8', 'nt_platform': 2, 'import_name': 'GetLocaleInfoA', 'iat': '0x0065711C', 'fallback': {'offset': 39, 'type': 'DIR32', 'symbol': '_crtGetLocaleInfoA@16', 'addend': 0, 'local_symbol_offset': None, 'target_address': '0x0064D222', 'target_kind': 'code-entry', 'code_entry': {'owner': '0x0064D222', 'source_member_offset': 1324526, 'source_offset': 0, 'source_definition': {'symbol': '_crtGetLocaleInfoA@16', 'offset': 0, 'section': 140, 'type': 32, 'storage': 3}}}, 'call_sites': ['0x0064D9C6', '0x0064D9E1', '0x0064D1E5', '0x0064D490', '0x0064D4E0', '0x0064D5B1', '0x0064D40F', '0x0064D6AA', '0x0064D38B'], 'basis': 'Actual complete source/target selection supports NT raw API or full stdcall compatibility helper; image starts null; runtime selection and locale results unknown'}

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def manifest():
    m = json.loads((ROOT / 'config/locale-construction-origin-evidence.json').read_text())
    identity = module('locale_construction_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R136' or m['target_sha256'] != identity.TARGET:
        raise ValueError('Input-format target identity differs')
    return m


def check_code_entry(binding, graph):
    entry = binding['code_entry']; owner = graph.get(entry['owner'])
    if not owner or owner['decision'] not in ('library','library-control','anchor'):
        raise ValueError('dispatch retains an unreviewed actual code entry')
    source = entry['source_definition']; primary = owner['source_definition']
    if (entry['source_member_offset'] != owner['member_offset']
            or source['symbol'] != binding['symbol'] or source['section'] != primary['section']
            or source['offset'] - primary['offset'] != entry['source_offset']
            or source['storage'] not in (2,3,6)
            or not any(r['offset']<=entry['source_offset']<r['offset']+r['size'] for r in owner['code_regions'])
            or int(binding['target_address'],16) != int(owner['address'],16) + entry['source_offset']):
        raise ValueError('dispatch code pointer loses its actual defining source owner/entry')


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(m['functions']) != 23 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete locale-construction cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != CODE_SIZES[key]
                or row['ledger_size'] != LEDGER_SIZES[key]
                or row['decision'] != 'library' or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'],16) != int(key,16) + size - 1):
            raise ValueError('locale-construction function loses its complete own auxiliary extent')
    auxiliary = {r['address']:(r['coff_symbol'],r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies'])!=3 or auxiliary!=AUXILIARIES or any(
            r['decision']!='library-control' or r['extent_basis']!='function-auxiliary-record'
            or r['code_size']!=r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16)!=int(r['address'],16)+r['size']-1 for r in m['auxiliary_bodies']):
        raise ValueError('locale-construction loses complete auxiliary owners')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'],r['size'],r['source_offset'],r['source_symbol']) for r in m['interior_labels']} != LABELS
            or any(r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary' for r in m['interior_labels'])):
        raise ValueError('locale-construction shared entries lose complete source parents or gain standalone credit')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence']) for r in m['anchors']] != ANCHORS:
        raise ValueError('locale-construction independent complete anchors differ')
    if any(m[k] for k in (
                          'range_markers','initializer_registrations','callback_ranges','literal_controls')):
        raise ValueError('locale-construction graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 198 or sum(r['size'] for r in m['state_data']) != 6378
            or {(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in m['state_data']} != STATE):
        raise ValueError('locale-construction graph loses complete defining sections or substitutes carrier prefixes')
    if m['sdk_layout']['source_section_size'] != 340 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS:
        raise ValueError('natural locale-construction operation/layout controls differ')
    if m['retained_controls'] != [dict(evidence_id='R135',manifest='input-format-origin-evidence.json')]:
        raise ValueError('locale-construction loses independently retained complete runtime/game controls')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors'] + m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] not in ('state','import'):
                raise ValueError('locale-construction graph retains an unsupported data/API/code dependency')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('locale-construction shared branch loses its actual complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('locale-construction direct edge uses unsupported extent evidence')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('locale-construction table loses full typed entry provenance')
            if b['target_kind']=='code-entry':
                check_code_entry(b, graph)
    check_parent_protocol(m, graph)
    return rows


def check_parent_protocol(m, graph):
    if m['locale_protocol']!=IO_PROTOCOL or m['call_controls']!=CALL_CONTROLS:
        raise ValueError('locale complete layouts and cdecl/stdcall callback protocol differ')
    if any(m[k] for k in ('interior_labels','retained_labels','diagnostic_contexts','scope_tables',
                          'code_carriers','extent_reconciliations','source_alternatives')):
        raise ValueError('locale gains unresolved owners or invented standalone credit')
    if set(m['vendor_sources'])!=VENDOR_SOURCES:
        raise ValueError('locale loses complete defining vendor sources')
    if m['common_globals']!=COMMON_GLOBALS:
        raise ValueError('locale loses five complete defining COMMON declarations')
    for row in graph.values():
        expected=MEMCPY_REGIONS if row['address']=='0x00640F20' else [dict(offset=0,size=row['size'])]
        if row['code_regions']!=expected or row['code_size']!=sum(r['size'] for r in expected):
            raise ValueError('locale loses complete code/data partition of its full source owner')
        if row['address']!='0x00640F20' and row.get('embedded_tables'):
            raise ValueError('locale gains unsupported embedded tables')
    if graph['0x00640F20'].get('embedded_tables')!=MEMCPY_TABLES:
        raise ValueError('locale memcpy anchor loses all six whole embedded tables')
    for table in MEMCPY_TABLES:
        for entry in table['entries']:check_code_entry(entry,graph)
    category=m['category_dispatch']
    if category!=CATEGORY_DISPATCH:
        raise ValueError('locale loses complete six-record category callback graph')
    table=next(r for r in m['state_data'] if r['symbol']=='___lc_category')
    fields=[b for b in table['relocations'] if b['target_kind']=='code-entry']
    if (table['size']!=72 or len(table['relocations'])!=17 or len(fields)!=6
            or [b['offset'] for b in fields]!=[8,20,32,44,56,68]
            or [b['target_address'] for b in fields]!=[e['target_address'] for e in category['entries']]
            or [b['code_entry'] for b in fields]!=[e['code_entry'] for e in category['entries']]):
        raise ValueError('locale category table loses full source fields and actual initializers')
    for entry in category['entries']:check_code_entry(entry,graph)
    registrations=m['callback_registrations']
    if registrations!=CALLBACK_REGISTRATIONS:
        raise ValueError('locale loses three actual SDK enumeration registrations')
    for registration in registrations:
        row=graph[registration['caller']]
        fields=[b for b in row['relocation_bindings'] if b['offset']==registration['field_offset']]
        if (len(fields)!=1 or fields[0]['target_kind']!='code-entry'
                or fields[0]['type']!='DIR32' or fields[0]['target_address']!=registration['callback']
                or fields[0]['code_entry']!=registration['code_entry']
                or graph[registration['callback']]['member_offset']!=row['member_offset']):
            raise ValueError('locale enumeration field loses actual defining callback owner')
        if {r['cleanup'] for r in graph[registration['callback']]['body_facts']['returns']}!={4}:
            raise ValueError('locale enumeration callback loses real RET 4')
    dispatch=m['query_dispatch']
    if dispatch!=QUERY_DISPATCH:
        raise ValueError('locale loses actual null/NT/API/fallback query selection')
    state=next(r for r in m['state_data'] if r['symbol']=='_iLcidState')
    if (state['size']!=36 or state['target_address']!='0x0068E690'
            or not state.get('zero_fill_region')
            or not any(d['symbol']=='_pfnGetLocaleInfoA' and d['offset']==32 for d in state['source_section']['definitions'])):
        raise ValueError('locale query pointer loses complete defining BSS carrier')
    fallback=dispatch['fallback'];check_code_entry(fallback,graph)
    field=next(b for b in graph[dispatch['owner']]['relocation_bindings'] if b['offset']==39)
    if field!=fallback or {r['cleanup'] for r in graph['0x0064D222']['body_facts']['returns']}!={16}:
        raise ValueError('locale fallback loses actual typed store or real RET 16')
    actual_sites=[w['site'] for r in m['functions'] for w in r['instruction_witnesses']
                  if w['mnemonic']=='call' and w['operands']=='dword ptr [0x68e6b0]']
    if actual_sites!=dispatch['call_sites']:
        raise ValueError('locale query loses every actual indirect call site')
    witnesses=lambda key:{(w['mnemonic'],w['operands']) for w in graph[key]['instruction_witnesses']}
    required={
        '0x00643041':{('call','dword ptr [ebx + 0x6700c0]'),('mov','dword ptr [ebx + 0x6700bc], eax'),('mov','dword ptr [0x68e6cc], eax')},
        '0x0064D853':{('cmp','dword ptr [0x68e2e8], 2'),('mov','dword ptr [0x68e6b0], eax'),('mov','dword ptr [0x68e6b0], 0x64d222'),('call','dword ptr [0x657110]'),('call','dword ptr [0x657114]')},
        '0x0064CD5F':{('mov','dword ptr [esp], 0x300'),('mov','dword ptr [esp], 0x101'),('push','0xfe')},
        '0x00642EE5':{('mov','edi, 0x82'),('push','6'),('push','4')},
    }
    for key,expected in required.items():
        if not expected<=witnesses(key):
            raise ValueError('locale loses cache/category/qualification/ctype behavior witnesses')


def decode_code(row,raw,address,decoder):
    return [i for region in row['code_regions']
            for i in decoder.disasm(raw[region['offset']:region['offset']+region['size']],address+region['offset'])]


def check_dispatch_instructions(m,decoded):
    by_address=lambda key:{i.address:i for i in decoded[key]}
    for registration in m['callback_registrations']:
        instructions=decoded[registration['caller']];sites=by_address(registration['caller'])
        push=sites[int(registration['push_site'],16)];call=sites[int(registration['call_site'],16)]
        flag=sites[int(registration['flag_site'],16)]
        argument_instructions=[i for i in instructions if flag.address<=i.address<call.address]
        if ((push.mnemonic,push.op_str)!=('push',hex(int(registration['callback'],16)))
                or (flag.mnemonic,flag.op_str)!=('push','1')
                or [i.address for i in argument_instructions if i.mnemonic=='push']!=[flag.address,push.address]
                or any(i.mnemonic not in ('push','inc','mov') for i in argument_instructions)
                or (call.mnemonic,call.op_str)!=('call','dword ptr [0x657118]')):
            raise ValueError('locale enumeration loses real push/installed-flag/API call contract')
    category=m['category_dispatch'];call=by_address('0x00643041')[int(category['call_site'],16)]
    if (call.mnemonic,call.op_str)!=('call',category['operand']):
        raise ValueError('locale category loses actual initializer indirect instruction')


def check_memcpy_partition(row,actual,instructions):
    if row['address']!='0x00640F20':return
    base=int(row['address'],16);starts={i.address for i in instructions};fields=row['relocation_bindings']
    covered=set()
    for region in row['code_regions']:
        covered.update(range(region['offset'],region['offset']+region['size']))
    for table in row['embedded_tables']:
        definition=table['source_definition']
        if (definition['symbol']!=table['symbol'] or definition['offset']!=table['offset']
                or definition['section']!=row['source_definition']['section']):
            raise ValueError('memcpy table loses actual whole source definition')
        data_offsets=set(range(table['offset'],table['offset']+table['size']))
        if covered&data_offsets:raise ValueError('memcpy table is incorrectly decoded as code')
        covered.update(data_offsets)
        values=struct.unpack('<'+'I'*(table['size']//4),actual[table['offset']:table['offset']+table['size']])
        if [f'0x{x:08X}' for x in values]!=[e['target_address'] for e in table['entries']] or any(x not in starts for x in values):
            raise ValueError('memcpy whole table loses actual code case starts')
        for entry in table['entries']:
            field=next(b for b in fields if b['offset']==entry['offset'])
            if (field['type']!='DIR32' or field['symbol']!=entry['symbol']
                    or field['target_address']!=entry['target_address']):
                raise ValueError('memcpy table loses its full source-typed field')
    if covered!=set(range(row['size'])):
        raise ValueError('memcpy source partition omits or pads complete owner bytes')


def object_code(path, row, comparison, coff):
    if row['extent_basis']!='function-auxiliary-record':
        raise ValueError('locale-construction function loses its complete own AUX extent')
    return comparison.object_function(path,row['coff_symbol'])


def check_interior_entry(label, parent, definitions, target_ins, source_ins):
    offset=label['source_offset'];base=int(parent['address'],16)
    if int(label['address'],16)!=base+offset or base+offset not in {i.address for i in target_ins}:
        raise ValueError('shared entry loses actual complete-owner instruction start')
    if label['source_symbol'] is not None:
        actual=next((d for d in definitions if d['symbol']==label['source_symbol']
                     and d['section']==parent['source_definition']['section']),None)
        if (actual!=label['source_definition'] or actual is None or actual['storage'] not in (2,3,6)
                or actual['offset']-parent['source_definition']['offset']!=offset):
            raise ValueError('shared entry loses actual full-owner defining source symbol')
    else:
        raise ValueError('locale-construction cleanup gains an invented source entry')


def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-construction loses complete origin-only extent')
    if (origin['evidence_id'] != 'R136' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('locale-construction canonical complete library acceptance differs')


def check_label(row, function, origin, functions, origins, graph):
    parent = graph[row['parent']]
    if parent['decision'] == 'library':
        check_ledger(parent, functions[parent['address']], origins[parent['address']])
    elif parent['decision'] != 'library-control' or parent['address'] in functions:
        raise ValueError('locale-construction shared entry loses its complete non-inventoried parent')
    if (origin['evidence_id'] != 'R136' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != LABEL_CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] or int(function['size']) != row['size']
            or int(function['span_end'],16) != int(row['address'],16) + row['size'] - 1
            or function['source_file'] or function['match_percent'] != '0.00'):
        raise ValueError('locale-construction shared entry gains unsupported standalone/source/exact credit')


def resolve_state_reference(use, state_map, global_state):
    key = (use['member_offset'],use['symbol'])
    dest = state_map.get(key)
    if dest is None:
        values = global_state.get(use['symbol'],set())
        if len(values) != 1:
            raise ValueError('locale-construction external data reference lacks a whole strong definition')
        dest = next(iter(values))
    if dest != int(use['target_address'],16):
        raise ValueError('locale-construction member-local data reference changes its actual defining object')
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('locale_construction_old','verify-runtime-error-origins.py')
    c = module('locale_construction_target','compare-coff-function.py')
    archive_reader = module('locale_construction_archive','verify-runtime-origins.py')
    coff = module('locale_construction_coff','coff_data.py')
    startup = module('locale_construction_geometry','verify-startup-dependency-origins.py')
    record = module('locale_construction_ledger','verify-vendor-record-origins.py')
    facts = module('locale_construction_facts','verify-game-lifetime-origins.py')
    imports_module = module('locale_construction_imports','verify-import-origins.py')
    literal = module('locale_construction_scalar','verify-runtime-external-origins.py')
    sections = module('locale_construction_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete locale-construction source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('locale-construction complete primary loses an actual interior candidate')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned whole CRT archive differs')
    members = {off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    def member(row):
        name,data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data
    target_sections = sections.sections(target); imports = imports_module.pe_imports(target,c)
    state_map = {}; global_state = {}
    for row in m['state_data']:
        raw,desc = old.whole_section(member(row),row['symbol'],c,coff)
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('locale-construction whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('locale-construction source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('locale-construction state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('locale-construction whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('locale-construction initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('locale-construction complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('locale-construction state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    for row in m['common_globals']:
        definitions=coff.parse_symbols(member(row),c.coff_name)[1]
        actual=next((d for d in definitions if d['symbol']==row['symbol'] and d['section']==0),None)
        a=int(row['target_address'],16)
        if actual!=row['source_definition'] or actual['offset']!=row['size'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:
            raise ValueError('complete COMMON definition/loader zero-fill differs')
        state_map[(row['member_offset'],row['symbol'])]=a
        global_state.setdefault(row['symbol'],set()).add(a)
    for use in m['state_uses']:
        state_map[(use['member_offset'],use['symbol'])] = resolve_state_reference(use,state_map,global_state)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-locale-construction-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural locale-construction control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned locale-construction control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_LocaleConstructionLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural locale-construction data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural handle/thread/SDK offsets or constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete locale-construction vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete input pointer-varargs/int64/PF2 controls differ')
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != 'library' or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R135'):
                    raise ValueError('locale-construction retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'])
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('locale-construction complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('locale-construction full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('locale-construction whole code instruction/control-flow inventory differs')
            check_memcpy_partition(row,actual,ins)
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('locale-construction complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('locale-construction field lacks member-local/whole strong data provenance')
        check_dispatch_instructions(m,decoded)
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('locale-construction code entry catalog differs from actual complete source definitions')
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decoder.disasm(code[:row['code_size']],row['source_definition']['offset'])}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('locale-construction local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('locale-construction direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('locale-construction direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('locale-construction same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-construction shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('locale-construction complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('locale-construction data pointer does not reach a complete actual code entry')
        for label in m['interior_labels']+m['retained_labels']:
            parent = graph[label['parent']]
            path.write_bytes(member(parent))
            defs = coff.parse_symbols(member(parent),c.coff_name)[1]
            source,_=object_code(path,parent,c,coff)
            source_ins=list(decoder.disasm(source,parent['source_definition']['offset']))
            check_interior_entry(label,parent,defs,decoded[parent['address']],source_ins)
            if label['decision']=='retained':
                origin=origins[label['address']];function=functions[label['address']]
                if origin['evidence_id']!=label['origin_evidence'] or origin['origin']!='library' or int(function['size'])!=label['size'] or function['source_file'] or function['match_percent']!='0.00':
                    raise ValueError('retained shared entry gains unsupported new acceptance')
            elif not args.evidence_only:
                check_label(label,functions[label['address']],origins[label['address']],functions,origins,graph)
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-input-format-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('retained independent complete R135 graph replay failed: '+result.stderr[-1500:])
    print('R136 origins OK: twenty-three complete library primaries / 5949 bytes / 421 typed fields; three non-inventoried category controls / 101 bytes / ten fields; twenty-five full anchors / 4402 bytes / 215 fields; 198 whole data sections / 6378 bytes / 220 fields; five complete COMMON declarations / 20 bytes; six actual category initializers, three installed-locale enumeration registrations and complete NT/API/fallback dispatch; full 829-byte memcpy with seven code regions and six tables; cold 340-byte natural layout and 45-/17-/8-/24-byte callback/API controls; full retained R135 graph; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
