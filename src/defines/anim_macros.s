.text
.thumb

.macro loadparticle loadparticleID
.byte 0x0
.hword \loadparticleID
.endm

.macro unloadparticle unloadparticleID
.byte 0x1
.hword \unloadparticleID
.endm

.macro launchtemplate launchtemplatePtr launchtemplateUnkown launchtemplateArgsNo
.byte 0x2
.word \launchtemplatePtr
.byte \launchtemplateUnkown
.byte \launchtemplateArgsNo
.endm

.macro launchtask launchtaskPtr launchtaskUnkown launchtaskArgsNo
.byte 0x3
.word \launchtaskPtr
.byte \launchtaskUnkown
.byte \launchtaskArgsNo
.endm

.macro pause_cmd pause_cmdToWait
.byte 0x4
.byte \pause_cmdToWait
.endm

.macro waitanimation
.byte 0x5
.endm

.macro endanimation
.byte 0x8
.endm

.macro playsound1 playsound1ID
.byte 0x9
.hword \playsound1ID
.endm

.macro animA animABank
.byte 0xA
.byte \animABank
.endm

.macro animB animBBank
.byte 0xB
.byte \animBBank
.endm

.macro set_BLDALPHA_BLDCNT set_BLDALPHA_value
.byte 0xC
.hword \set_BLDALPHA_value
.endm

.macro reset_BLDALPHA_BLDCNT
.byte 0xD
.endm

.macro call_cmd call_cmd_ptr
.byte 0xE
.word \call_cmd_ptr
.endm

.macro return_cmd
.byte 0xF
.endm

.macro setarg setargID setargValue
.byte 0x10
.byte \setargID
.hword \setargValue
.endm

.macro goto_cmd goto_cmdPtr
.byte 0x13
.word \goto_cmdPtr
.endm

.macro loadBG1 loadBG1ID
.byte 0x14
.byte \loadBG1ID
.endm

.macro loaddefaultBG
.byte 0x15
.endm

.macro waitforscreenelements1
.byte 0x16
.endm

.macro waitforscreenelements2
.byte 0x17
.endm

.macro loadBG2 loadBG2ID
.byte 0x18
.byte \loadBG2ID
.endm

.macro playsound2 playsound2ID playsound2Unkown
.byte 0x19
.hword \playsound2ID
.byte \playsound2Unkown
.endm

.macro anim1B anim1BsongID anim1BArg3 anim1BArg4 anim1BArg5 anim1BArg6
.byte 0x1B
.hword \anim1BsongID
.byte \anim1BArg3
.byte \anim1BArg4
.byte \anim1BArg5
.byte \anim1BArg6
.endm

.macro anim1C anim1Carg1 anim1Carg2 anim1Carg3 anim1Carg4
.byte 0x1C
.hword \anim1Carg1
.byte \anim1Carg2
.byte \anim1Carg3
.byte \anim1Carg4
.endm

.macro anim1D anim1Darg1 anim1Darg2 anim1Darg3
.byte 0x1D
.hword \anim1Darg1
.byte \anim1Darg2
.byte \anim1Darg3
.endm

.macro set_BLDCNT set_BLDCNTvalue
.byte 0x1E
.hword \set_BLDCNTvalue
.endm

.macro jumpifargmatches jumpifargmatchesargID jumpifargmatchesValue jumpifargmatchesPtr
.byte 0x21
.byte \jumpifargmatchesargID
.hword \jumpifargmatchesValue
.word \jumpifargmatchesPtr
.endm

.macro anim28 anim28Bank
.byte 0x28
.byte \anim28Bank
.endm

.macro setBGprioritiestoBGIDs
.byte 0x29
.endm

.macro makebankinvisible makebankinvisibleBank
.byte 0x2B
.byte \makebankinvisibleBank
.endm

.macro makebankvisible makebankvisibleBank
.byte 0x2C
.byte \makebankvisibleBank
.endm

.macro stopmusic
.byte 0x2F
.endm

.macro objtemplate objtemplatetiletag objtemplatepaltag objtemplateoam objtemplateimageanim objtemplategfx objtemplaterotscale objtemplatecallback
.hword \objtemplatetiletag
.hword \objtemplatepaltag
.word \objtemplateoam
.word \objtemplateimageanim
.word \objtemplategfx
.word \objtemplaterotscale
.word \objtemplatecallback
.endm
