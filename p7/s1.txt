
s1:     file format elf32-i386


Disassembly of section .init:

00001000 <_init>:
    1000:	f3 0f 1e fb          	endbr32 
    1004:	53                   	push   %ebx
    1005:	83 ec 08             	sub    $0x8,%esp
    1008:	e8 03 01 00 00       	call   1110 <__x86.get_pc_thunk.bx>
    100d:	81 c3 ab 2f 00 00    	add    $0x2fab,%ebx
    1013:	8b 83 38 00 00 00    	mov    0x38(%ebx),%eax
    1019:	85 c0                	test   %eax,%eax
    101b:	74 02                	je     101f <_init+0x1f>
    101d:	ff d0                	call   *%eax
    101f:	83 c4 08             	add    $0x8,%esp
    1022:	5b                   	pop    %ebx
    1023:	c3                   	ret    

Disassembly of section .plt:

00001030 <__libc_start_main@plt-0x10>:
    1030:	ff b3 04 00 00 00    	push   0x4(%ebx)
    1036:	ff a3 08 00 00 00    	jmp    *0x8(%ebx)
    103c:	00 00                	add    %al,(%eax)
	...

00001040 <__libc_start_main@plt>:
    1040:	ff a3 0c 00 00 00    	jmp    *0xc(%ebx)
    1046:	68 00 00 00 00       	push   $0x0
    104b:	e9 e0 ff ff ff       	jmp    1030 <_init+0x30>

00001050 <fgets@plt>:
    1050:	ff a3 10 00 00 00    	jmp    *0x10(%ebx)
    1056:	68 08 00 00 00       	push   $0x8
    105b:	e9 d0 ff ff ff       	jmp    1030 <_init+0x30>

00001060 <sleep@plt>:
    1060:	ff a3 14 00 00 00    	jmp    *0x14(%ebx)
    1066:	68 10 00 00 00       	push   $0x10
    106b:	e9 c0 ff ff ff       	jmp    1030 <_init+0x30>

00001070 <__stack_chk_fail@plt>:
    1070:	ff a3 18 00 00 00    	jmp    *0x18(%ebx)
    1076:	68 18 00 00 00       	push   $0x18
    107b:	e9 b0 ff ff ff       	jmp    1030 <_init+0x30>

00001080 <puts@plt>:
    1080:	ff a3 1c 00 00 00    	jmp    *0x1c(%ebx)
    1086:	68 20 00 00 00       	push   $0x20
    108b:	e9 a0 ff ff ff       	jmp    1030 <_init+0x30>

00001090 <exit@plt>:
    1090:	ff a3 20 00 00 00    	jmp    *0x20(%ebx)
    1096:	68 28 00 00 00       	push   $0x28
    109b:	e9 90 ff ff ff       	jmp    1030 <_init+0x30>

000010a0 <fopen@plt>:
    10a0:	ff a3 24 00 00 00    	jmp    *0x24(%ebx)
    10a6:	68 30 00 00 00       	push   $0x30
    10ab:	e9 80 ff ff ff       	jmp    1030 <_init+0x30>

000010b0 <__printf_chk@plt>:
    10b0:	ff a3 28 00 00 00    	jmp    *0x28(%ebx)
    10b6:	68 38 00 00 00       	push   $0x38
    10bb:	e9 70 ff ff ff       	jmp    1030 <_init+0x30>

000010c0 <strtol@plt>:
    10c0:	ff a3 2c 00 00 00    	jmp    *0x2c(%ebx)
    10c6:	68 40 00 00 00       	push   $0x40
    10cb:	e9 60 ff ff ff       	jmp    1030 <_init+0x30>

Disassembly of section .plt.got:

000010d0 <__cxa_finalize@plt>:
    10d0:	ff a3 34 00 00 00    	jmp    *0x34(%ebx)
    10d6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

000010e0 <_start>:
    10e0:	f3 0f 1e fb          	endbr32 
    10e4:	31 ed                	xor    %ebp,%ebp
    10e6:	5e                   	pop    %esi
    10e7:	89 e1                	mov    %esp,%ecx
    10e9:	83 e4 f0             	and    $0xfffffff0,%esp
    10ec:	50                   	push   %eax
    10ed:	54                   	push   %esp
    10ee:	52                   	push   %edx
    10ef:	e8 18 00 00 00       	call   110c <_start+0x2c>
    10f4:	81 c3 c4 2e 00 00    	add    $0x2ec4,%ebx
    10fa:	6a 00                	push   $0x0
    10fc:	6a 00                	push   $0x0
    10fe:	51                   	push   %ecx
    10ff:	56                   	push   %esi
    1100:	ff b3 40 00 00 00    	push   0x40(%ebx)
    1106:	e8 35 ff ff ff       	call   1040 <__libc_start_main@plt>
    110b:	f4                   	hlt    
    110c:	8b 1c 24             	mov    (%esp),%ebx
    110f:	c3                   	ret    

00001110 <__x86.get_pc_thunk.bx>:
    1110:	8b 1c 24             	mov    (%esp),%ebx
    1113:	c3                   	ret    
    1114:	66 90                	xchg   %ax,%ax
    1116:	66 90                	xchg   %ax,%ax
    1118:	66 90                	xchg   %ax,%ax
    111a:	66 90                	xchg   %ax,%ax
    111c:	66 90                	xchg   %ax,%ax
    111e:	66 90                	xchg   %ax,%ax

00001120 <deregister_tm_clones>:
    1120:	e8 e4 00 00 00       	call   1209 <__x86.get_pc_thunk.dx>
    1125:	81 c2 93 2e 00 00    	add    $0x2e93,%edx
    112b:	8d 8a 6c 00 00 00    	lea    0x6c(%edx),%ecx
    1131:	8d 82 6c 00 00 00    	lea    0x6c(%edx),%eax
    1137:	39 c8                	cmp    %ecx,%eax
    1139:	74 1d                	je     1158 <deregister_tm_clones+0x38>
    113b:	8b 82 30 00 00 00    	mov    0x30(%edx),%eax
    1141:	85 c0                	test   %eax,%eax
    1143:	74 13                	je     1158 <deregister_tm_clones+0x38>
    1145:	55                   	push   %ebp
    1146:	89 e5                	mov    %esp,%ebp
    1148:	83 ec 14             	sub    $0x14,%esp
    114b:	51                   	push   %ecx
    114c:	ff d0                	call   *%eax
    114e:	83 c4 10             	add    $0x10,%esp
    1151:	c9                   	leave  
    1152:	c3                   	ret    
    1153:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    1157:	90                   	nop
    1158:	c3                   	ret    
    1159:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00001160 <register_tm_clones>:
    1160:	e8 a4 00 00 00       	call   1209 <__x86.get_pc_thunk.dx>
    1165:	81 c2 53 2e 00 00    	add    $0x2e53,%edx
    116b:	55                   	push   %ebp
    116c:	89 e5                	mov    %esp,%ebp
    116e:	53                   	push   %ebx
    116f:	8d 8a 6c 00 00 00    	lea    0x6c(%edx),%ecx
    1175:	8d 82 6c 00 00 00    	lea    0x6c(%edx),%eax
    117b:	83 ec 04             	sub    $0x4,%esp
    117e:	29 c8                	sub    %ecx,%eax
    1180:	89 c3                	mov    %eax,%ebx
    1182:	c1 e8 1f             	shr    $0x1f,%eax
    1185:	c1 fb 02             	sar    $0x2,%ebx
    1188:	01 d8                	add    %ebx,%eax
    118a:	d1 f8                	sar    %eax
    118c:	74 14                	je     11a2 <register_tm_clones+0x42>
    118e:	8b 92 44 00 00 00    	mov    0x44(%edx),%edx
    1194:	85 d2                	test   %edx,%edx
    1196:	74 0a                	je     11a2 <register_tm_clones+0x42>
    1198:	83 ec 08             	sub    $0x8,%esp
    119b:	50                   	push   %eax
    119c:	51                   	push   %ecx
    119d:	ff d2                	call   *%edx
    119f:	83 c4 10             	add    $0x10,%esp
    11a2:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    11a5:	c9                   	leave  
    11a6:	c3                   	ret    
    11a7:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    11ae:	66 90                	xchg   %ax,%ax

000011b0 <__do_global_dtors_aux>:
    11b0:	f3 0f 1e fb          	endbr32 
    11b4:	55                   	push   %ebp
    11b5:	89 e5                	mov    %esp,%ebp
    11b7:	53                   	push   %ebx
    11b8:	e8 53 ff ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    11bd:	81 c3 fb 2d 00 00    	add    $0x2dfb,%ebx
    11c3:	83 ec 04             	sub    $0x4,%esp
    11c6:	80 bb 6c 00 00 00 00 	cmpb   $0x0,0x6c(%ebx)
    11cd:	75 27                	jne    11f6 <__do_global_dtors_aux+0x46>
    11cf:	8b 83 34 00 00 00    	mov    0x34(%ebx),%eax
    11d5:	85 c0                	test   %eax,%eax
    11d7:	74 11                	je     11ea <__do_global_dtors_aux+0x3a>
    11d9:	83 ec 0c             	sub    $0xc,%esp
    11dc:	ff b3 4c 00 00 00    	push   0x4c(%ebx)
    11e2:	e8 e9 fe ff ff       	call   10d0 <__cxa_finalize@plt>
    11e7:	83 c4 10             	add    $0x10,%esp
    11ea:	e8 31 ff ff ff       	call   1120 <deregister_tm_clones>
    11ef:	c6 83 6c 00 00 00 01 	movb   $0x1,0x6c(%ebx)
    11f6:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    11f9:	c9                   	leave  
    11fa:	c3                   	ret    
    11fb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    11ff:	90                   	nop

00001200 <frame_dummy>:
    1200:	f3 0f 1e fb          	endbr32 
    1204:	e9 57 ff ff ff       	jmp    1160 <register_tm_clones>

00001209 <__x86.get_pc_thunk.dx>:
    1209:	8b 14 24             	mov    (%esp),%edx
    120c:	c3                   	ret    

0000120d <fail>:
    120d:	56                   	push   %esi
    120e:	53                   	push   %ebx
    120f:	83 ec 10             	sub    $0x10,%esp
    1212:	e8 f9 fe ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    1217:	81 c3 a1 2d 00 00    	add    $0x2da1,%ebx
    121d:	6a 01                	push   $0x1
    121f:	e8 3c fe ff ff       	call   1060 <sleep@plt>
    1224:	8d b3 50 e0 ff ff    	lea    -0x1fb0(%ebx),%esi
    122a:	89 34 24             	mov    %esi,(%esp)
    122d:	e8 4e fe ff ff       	call   1080 <puts@plt>
    1232:	8d 83 78 e0 ff ff    	lea    -0x1f88(%ebx),%eax
    1238:	89 04 24             	mov    %eax,(%esp)
    123b:	e8 40 fe ff ff       	call   1080 <puts@plt>
    1240:	89 34 24             	mov    %esi,(%esp)
    1243:	e8 38 fe ff ff       	call   1080 <puts@plt>
    1248:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    124f:	e8 3c fe ff ff       	call   1090 <exit@plt>

00001254 <success>:
    1254:	56                   	push   %esi
    1255:	53                   	push   %ebx
    1256:	83 ec 10             	sub    $0x10,%esp
    1259:	e8 b2 fe ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    125e:	81 c3 5a 2d 00 00    	add    $0x2d5a,%ebx
    1264:	6a 01                	push   $0x1
    1266:	e8 f5 fd ff ff       	call   1060 <sleep@plt>
    126b:	8d b3 a0 e0 ff ff    	lea    -0x1f60(%ebx),%esi
    1271:	89 34 24             	mov    %esi,(%esp)
    1274:	e8 07 fe ff ff       	call   1080 <puts@plt>
    1279:	8d 83 c4 e0 ff ff    	lea    -0x1f3c(%ebx),%eax
    127f:	89 04 24             	mov    %eax,(%esp)
    1282:	e8 f9 fd ff ff       	call   1080 <puts@plt>
    1287:	89 34 24             	mov    %esi,(%esp)
    128a:	e8 f1 fd ff ff       	call   1080 <puts@plt>
    128f:	83 c4 14             	add    $0x14,%esp
    1292:	5b                   	pop    %ebx
    1293:	5e                   	pop    %esi
    1294:	c3                   	ret    

00001295 <main>:
    1295:	8d 4c 24 04          	lea    0x4(%esp),%ecx
    1299:	83 e4 f0             	and    $0xfffffff0,%esp
    129c:	ff 71 fc             	push   -0x4(%ecx)
    129f:	55                   	push   %ebp
    12a0:	89 e5                	mov    %esp,%ebp
    12a2:	57                   	push   %edi
    12a3:	56                   	push   %esi
    12a4:	53                   	push   %ebx
    12a5:	51                   	push   %ecx
    12a6:	81 ec 28 02 00 00    	sub    $0x228,%esp
    12ac:	e8 5f fe ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    12b1:	81 c3 07 2d 00 00    	add    $0x2d07,%ebx
    12b7:	8b 51 04             	mov    0x4(%ecx),%edx
    12ba:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
    12c0:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    12c3:	31 c0                	xor    %eax,%eax
    12c5:	8b 83 3c 00 00 00    	mov    0x3c(%ebx),%eax
    12cb:	8b 38                	mov    (%eax),%edi
    12cd:	83 39 02             	cmpl   $0x2,(%ecx)
    12d0:	74 6f                	je     1341 <main+0xac>
    12d2:	be 01 00 00 00       	mov    $0x1,%esi
    12d7:	8b 83 3c 00 00 00    	mov    0x3c(%ebx),%eax
    12dd:	89 85 d4 fd ff ff    	mov    %eax,-0x22c(%ebp)
    12e3:	8d 83 ea e0 ff ff    	lea    -0x1f16(%ebx),%eax
    12e9:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%ebp)
    12ef:	83 fe 06             	cmp    $0x6,%esi
    12f2:	74 7f                	je     1373 <main+0xde>
    12f4:	8b 85 d4 fd ff ff    	mov    -0x22c(%ebp),%eax
    12fa:	39 38                	cmp    %edi,(%eax)
    12fc:	74 5f                	je     135d <main+0xc8>
    12fe:	83 ec 04             	sub    $0x4,%esp
    1301:	57                   	push   %edi
    1302:	68 00 02 00 00       	push   $0x200
    1307:	8d 85 e4 fd ff ff    	lea    -0x21c(%ebp),%eax
    130d:	50                   	push   %eax
    130e:	e8 3d fd ff ff       	call   1050 <fgets@plt>
    1313:	83 c4 10             	add    $0x10,%esp
    1316:	85 c0                	test   %eax,%eax
    1318:	74 d5                	je     12ef <main+0x5a>
    131a:	83 ec 04             	sub    $0x4,%esp
    131d:	6a 0a                	push   $0xa
    131f:	6a 00                	push   $0x0
    1321:	8d 85 e4 fd ff ff    	lea    -0x21c(%ebp),%eax
    1327:	50                   	push   %eax
    1328:	e8 93 fd ff ff       	call   10c0 <strtol@plt>
    132d:	83 c6 01             	add    $0x1,%esi
    1330:	83 c4 10             	add    $0x10,%esp
    1333:	39 84 b3 50 00 00 00 	cmp    %eax,0x50(%ebx,%esi,4)
    133a:	74 a7                	je     12e3 <main+0x4e>
    133c:	e8 cc fe ff ff       	call   120d <fail>
    1341:	83 ec 08             	sub    $0x8,%esp
    1344:	8d 83 e8 e0 ff ff    	lea    -0x1f18(%ebx),%eax
    134a:	50                   	push   %eax
    134b:	ff 72 04             	push   0x4(%edx)
    134e:	e8 4d fd ff ff       	call   10a0 <fopen@plt>
    1353:	89 c7                	mov    %eax,%edi
    1355:	83 c4 10             	add    $0x10,%esp
    1358:	e9 75 ff ff ff       	jmp    12d2 <main+0x3d>
    135d:	83 ec 04             	sub    $0x4,%esp
    1360:	56                   	push   %esi
    1361:	ff b5 d0 fd ff ff    	push   -0x230(%ebp)
    1367:	6a 01                	push   $0x1
    1369:	e8 42 fd ff ff       	call   10b0 <__printf_chk@plt>
    136e:	83 c4 10             	add    $0x10,%esp
    1371:	eb 8b                	jmp    12fe <main+0x69>
    1373:	e8 dc fe ff ff       	call   1254 <success>
    1378:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    137b:	65 2b 05 14 00 00 00 	sub    %gs:0x14,%eax
    1382:	75 11                	jne    1395 <main+0x100>
    1384:	b8 00 00 00 00       	mov    $0x0,%eax
    1389:	8d 65 f0             	lea    -0x10(%ebp),%esp
    138c:	59                   	pop    %ecx
    138d:	5b                   	pop    %ebx
    138e:	5e                   	pop    %esi
    138f:	5f                   	pop    %edi
    1390:	5d                   	pop    %ebp
    1391:	8d 61 fc             	lea    -0x4(%ecx),%esp
    1394:	c3                   	ret    
    1395:	e8 06 00 00 00       	call   13a0 <__stack_chk_fail_local>
    139a:	66 90                	xchg   %ax,%ax
    139c:	66 90                	xchg   %ax,%ax
    139e:	66 90                	xchg   %ax,%ax

000013a0 <__stack_chk_fail_local>:
    13a0:	f3 0f 1e fb          	endbr32 
    13a4:	53                   	push   %ebx
    13a5:	e8 66 fd ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    13aa:	81 c3 0e 2c 00 00    	add    $0x2c0e,%ebx
    13b0:	83 ec 08             	sub    $0x8,%esp
    13b3:	e8 b8 fc ff ff       	call   1070 <__stack_chk_fail@plt>

Disassembly of section .fini:

000013b8 <_fini>:
    13b8:	f3 0f 1e fb          	endbr32 
    13bc:	53                   	push   %ebx
    13bd:	83 ec 08             	sub    $0x8,%esp
    13c0:	e8 4b fd ff ff       	call   1110 <__x86.get_pc_thunk.bx>
    13c5:	81 c3 f3 2b 00 00    	add    $0x2bf3,%ebx
    13cb:	83 c4 08             	add    $0x8,%esp
    13ce:	5b                   	pop    %ebx
    13cf:	c3                   	ret    
