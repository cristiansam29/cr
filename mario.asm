; Configuración de la pantalla
PPUCTRL = $2000
PPUMASK = $2001
PPUSTATUS = $2002
OAMADDR = $2003
OAMDATA = $2004
PPUSCROLL = $2005
PPUADDR = $2006
PPUDATA = $2007

; Definición de variables
MarioX = $00 ; Posición horizontal de Mario
MarioY = $00 ; Posición vertical de Mario

; Definición de sprites
MarioSprites:
  .db $00,$00,$00,$00,$00,$00,$00,$00 ; Sprite vacío
  .db $18,$3C,$7E,$DB,$DB,$7E,$3C,$18 ; Sprite de Mario 1
  .db $18,$3C,$7E,$DB,$DB,$FF,$3C,$7E ; Sprite de Mario 2



; Configuración de sprites
  LDA #$84 ; Configuración de sprites (8x8, 2 paletas)
  STA PPUCTRL
  LDA #$1E ; Muestra los sprites y la pantalla
  STA PPUMASK
; Carga de sprites

LoadSprites:
  LDX #0 ; Índice de sprite
LoadSpritesLoop:
  LDA MarioSprites,X ; Carga el sprite en el registro A
  STA $0200,X ; Guarda el sprite en la memoria de sprites
  INX ; Incrementa el índice de sprite
  CPX #24 ; Comprueba si se han cargado todos los sprites
  BNE LoadSpritesLoop ; Si no se han cargado todos los sprites, vuelve al bucle

; Bucle principal
MainLoop:
  ; Ajusta la posición de la pantalla para que Mario se vea en el centro
  LDA #$20 ; Ajusta la posición horizontal de la pantalla
  STA PPUSCROLL
  LDA #$00 ; Ajusta la posición vertical de la pantalla
  STA PPUSCROLL+1
  
  ; Actualiza la posición de Mario
  LDA MarioX ; Carga la posición horizontal de Mario
  CMP #$F0 ; Comprueba si Mario está en el borde derecho de la pantalla
  BEQ TurnAround ; Si Mario está en el borde derecho, voltea
  
  INC MarioX ; Incrementa la posición horizontal de Mario
  JMP DrawMario ; Dibuja a Mario y vuelve al inicio del bucle
  
TurnAround:
  DEC MarioX ; Decrementa la posición horizontal de Mario
  JMP DrawMario ; Dibuja a Mario y vuelve al inicio del bucle

; Dibuja a Mario
DrawMario:
  ; Carga la dirección de memoria del sprite de Mario actual
  LDA #$00 ; Carga el número del sprite actual (en este caso, el primer sprite de Mario)
  CMP #$01 ; Comprueba si Mario ha avanzado una cierta cantidad de píxeles para mostrar el segundo sprite
  BCS LoadSecondSprite ; Si ha avanzado, carga el segundo sprite
  LDA #$0200 ; Carga la dirección de memoria del primer sprite de Mario
  JMP LoadSpriteAddress

LoadSecondSprite:
  LDA #$0208 ; Carga la dirección de memoria del segundo sprite de Mario

LoadSpriteAddress:
  STA OAMADDR ; Carga la dirección de memoria del primer sprite de Mario en el registro OAMADDR
  
  ; Dibuja el sprite de Mario
  LDX #$00 ; Carga el índice del sprite de Mario
  LDY #$00 ; Carga la posición vertical de Mario (en este caso, en la parte superior de la pantalla)
DrawSpriteLoop:
  LDA $0200,X ; Carga el byte de datos del sprite de Mario
  STA OAMDATA ; Guarda el byte de datos del sprite en la memoria de sprites
  INX ; Incrementa el índice del sprite
  CPX #$08 ; Comprueba si se han dibujado todos los bytes del sprite
  BNE DrawSpriteLoop ; Si no se han dibujado todos los bytes del sprite, vuelve al bucle
  
  ; Espera hasta que se complete el dibujo del sprite antes de volver a empezar el bucle
  LDA PPUSTATUS ; Lee el registro PPUSTATUS para esperar hasta que se complete el dibujo del sprite
  BPL DrawMario
  
  JMP MainLoop ; Vuelve al inicio del bucle principal
