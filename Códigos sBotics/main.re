#VARIAVEIS GLOBAIS
texto senEsq = Cor("lc1")
texto senDir = Cor("rc1")
texto senEsqEx  = Cor("lc2")
texto senDirEx = Cor("rc2")
texto senCen = Cor("lr0")

booleano becoSemSaida = falso
booleano verdeDireita = falso
booleano verdeEsquerda = falso
booleano naoAcheiSalaResgate = verdadeiro
booleano viVermelho = falso

numero erro = 0
numero senEsqL = Luz("lc1")
numero senDirL = Luz("rc1")
numero senEsqExL = Luz("lc2")
numero senDirExL = Luz("rc2")
numero senCenL = Luz("lr0")
numero senUltraF = Ultra("ultraF")
numero senUltraR = Ultra("ultraR")
numero senultraL = Ultra("ultraL")
numero senUltraV = Ultra("ultraV")
#ATUALIZAÇÃO DOS DADOS
tarefa FunAtua{ 
	senEsq = Cor("lc1")
	senDir = Cor("rc1")
	senEsqEx  = Cor("lc2")
	senDirEx = Cor("rc2")
	senCen = Cor("lr0")
	
	senUltraF = Ultra("ultraF")
	senUltraR = Ultra("ultraR")
	senultraL = Ultra("ultraL")
	senUltraV = Ultra("ultraV")

	senEsqL = Luz("lc1")
	senDirL = Luz("rc1")
	senCenL = Luz("lr0")
	senEsqExL = Luz("lc2")
	senDirExL = Luz("rc2")
}

#CONTROLE DA GARRINHA
tarefa InclinarGarrinha(numero forca){
	TravarMotor("atuaC",  falso)
	Motor("atuaC", forca)
	Esperar(180)
}

tarefa AbrirGarrinha(numero forca){
	TravarMotor("atuaL",falso)
	TravarMotor("atuaR",falso)
	Motor("atuaL", 0-forca)
	Motor("atuaR", forca)
	Esperar(450)
	TravarMotor("atuaL",verdadeiro)
	TravarMotor("atuaR",verdadeiro)
}

tarefa MoverGarrinha(numero forca){
	TravarMotor("atuaEixo",  falso)
	Motor("atuaEixo", forca)
	Esperar(1300)
	TravarMotor("atuaEixo",verdadeiro)
}
#ACHEI VERDE
tarefa VerificarBecoSemSaida{FunAtua()
	se((CorVerde("rc1") > CorAzul("rc1") e CorAzul("rc1") > CorVermelho("rc1")) e 
	(CorVerde("lc1") > CorAzul("lc1") e CorAzul("lc1") > CorVermelho("lc1")))entao{ becoSemSaida = verdadeiro
	}senao{becoSemSaida = falso}
}

tarefa VerificarVerdeDireita{FunAtua()
	se((CorVerde("rc1") > CorAzul("rc1") e CorAzul("rc1") > CorVermelho("rc1")) 
	ou (CorVerde("rc2") > CorAzul("rc2") e CorAzul("rc2") > CorVermelho("rc2")))entao{verdeDireita = verdadeiro
	}senao{verdeDireita = falso}
}

tarefa VerificarVerdeEsquerda{FunAtua()
	se((CorVerde("lc1") > CorAzul("lc1") e CorAzul("lc1") > CorVermelho("lc1")) 
	ou  (CorVerde("lc2") > CorAzul("lc2") e CorAzul("lc2") > CorVermelho("lc2")))entao{verdeEsquerda = verdadeiro
	}senao{verdeEsquerda = falso}
}
#CONTROLE DAS RODAS
tarefa DireitaEixoRobo (numero forca){
	Motor("lmotor", forca)
	Motor("lmotorTras",  forca)
	Motor("rmotorTras", 0- forca)
	Motor("rmotor", 0-forca)
	FunAtua()
}

tarefa EsquerdaEixoRobo (numero forca){
	Motor("rmotorTras",forca)
	Motor("rmotor", forca)
	Motor("lmotor", 0-forca)
	Motor("lmotorTras", 0-forca)
	FunAtua()
}

tarefa PararMotor (booleano trava = verdadeiro){ #Travando ou destravando os motores
	TravarMotor("rmotor",  trava)
	TravarMotor("lmotor",  trava)
	TravarMotor("rmotorTras",  trava)
	TravarMotor("lmotorTras",  trava)
}

tarefa Frente (numero forca){
	PararMotor(falso)
	Motor("rmotor", forca)
	Motor("lmotor", forca)
	Motor("rmotorTras", forca)
	Motor("lmotorTras", forca)
	FunAtua()
}

tarefa Tras (numero forca){
	Motor("rmotor", 0-forca)
	Motor("lmotor", 0-forca)
	Motor("rmotorTras", 0-forca)
	Motor("lmotorTras", 0-forca)
	FunAtua()
}

tarefa EsquerdaEixoRoda(numero forca){ #Eixo do robô
	Motor("rmotor", forca)
	Motor("lmotor",0-forca)
	Motor("rmotorTras", forca)
	Motor("lmotorTras", forca)
	FunAtua()
}

tarefa DireitaEixoRoda (numero forca){ #Eixo do robô
	Motor("rmotor",0-forca)
	Motor("lmotor", forca)
	Motor("rmotorTras", forca)
	Motor("lmotorTras", forca)
	FunAtua()
}
#SALA DE RESGATE
tarefa IdentificarSalaDeResgate{FunAtua()
	se((CorVerde("rc1") < CorAzul("rc1") e CorVerde("rc1") > CorVermelho("rc1")) 
	ou (CorVerde("lc1") < CorAzul("lc1") e CorVerde("lc1") > CorVermelho("lc1")) 
	ou (CorVerde("lr0") < CorAzul("lr0") e CorVerde("lr0") > CorVermelho("lr0")))entao{naoAcheiSalaResgate = falso}
}

#ACHEI VERMELHO
tarefa VerificarVermelho{FunAtua()
	se( ( (CorAzul("rc1") > CorVerde("rc1") e CorVermelho("rc1") > CorAzul("rc1")) 
	ou (CorAzul("rc2") > CorVerde("rc2") e CorVermelho("rc2") > CorAzul("rc2")) 
	e ((CorAzul("lc1") > CorVerde("lc1") e  CorVermelho("lc1") > CorAzul("lc1")) 
	ou (CorAzul("lc2") > CorVerde("lc2") e CorVermelho("lc2") > CorAzul("lc2"))) ))entao{viVermelho = verdadeiro
	}senao{viVermelho = falso}
}

tarefa pegarObjeto{
	PararMotor()
	InclinarGarrinha(0-200)
	AbrirGarrinha(0-200)
	MoverGarrinha(200)			
	AbrirGarrinha(200)
	InclinarGarrinha(200)
	MoverGarrinha(0-200)
	PararMotor(Falso)	
}

tarefa jogarObjeto{	
	PararMotor()
	InclinarGarrinha(0-200)
	MoverGarrinha(400)	
	AbrirGarrinha(0-200)		
	InclinarGarrinha(100)
	AbrirGarrinha(210)
	MoverGarrinha(0-290)
	PararMotor(Falso)	
}

tarefa Rotacionar{FunAtua()
	enquanto(senUltraF < 22 e ((Bussola() < 89 ou Bussola() > 91) ou (Bussola() > 269 ou Bussola() < 271)
							ou (Bussola() > 179 ou Bussola() < 181) ou (Bussola() > 1 ou Bussola() < 358)))farei{
		Esperar(60)
		DireitaEixoRobo(470)	
	}	
}

tarefa ProcurarVitima{Rotacionar()
	enquanto(senUltraV/senUltraF > 0.6)farei{#procurando vitimas
		DireitaEixoRobo(200)	
		Esperar(100)
	}
	enquanto(senUltraV/senUltraF <= 0.5)farei{#indo até a vitima
		FunAtua()
		se(senUltraV < 1.2 e senUltraV > 0)entao{pegarObjeto()
		}senao{Frente(100)}
		Esperar(50)
	}	
	enquanto(senUltraV/senUltraF > 0.8)farei{#procurando vitimas
		EsquerdaEixoRobo(200)	
		Esperar(90)
	}
}

tarefa ProcurarAreaDeResgate{FunAtua()
	se(senUltraF < 3 e senUltraF > 0)entao{
		PararMotor()
		Esperar(100)
		PararMotor(falso)
		Rotacionar()
	}senao  se(Toque("senToque"))entao{
				Esperar(350)
				jogarObjeto()
				Esperar(100)
				Tras(500)
				ProcurarVitima()
			}senao{Frente(200)}	
}
#DESAFIOS
tarefa ProcurarLinha(booleano direcao = verdadeiro){FunAtua()
	se(direcao)entao{ 
		enquanto(senCen != "Preto")farei{
			Esperar(50)
			DireitaEixoRobo(300)	
		}	
	}senao{
		enquanto(senCen != "Preto")farei{
			Esperar(50)
			EsquerdaEixoRobo(300)
		}	
	}
}

tarefa AcheiVerde{#Verificando pelo RGB
		VerificarBecoSemSaida()
		se(becoSemSaida)entao{ 
			Tras(250)
			Esperar(300)
			DireitaEixoRobo(700)
			Esperar(1000) 
			ProcurarLinha()   
			Tras(350)
			Esperar(500)
		}senao{VerificarVerdeDireita()
			se(verdeDireita)entao{        
					Frente(200)
					Esperar(500)    
					DireitaEixoRobo(700)
					Esperar(900) 
					Frente(100)
					Esperar(300)   
					ProcurarLinha()    
				}senao{VerificarVerdeEsquerda()
						se(verdeEsquerda)entao{ 
							Frente(200)
							Esperar(500)
							EsquerdaEixoRobo(700)
							Esperar(900) 
							Frente(100)
							Esperar(200)               
							ProcurarLinha(falso)   
						}
				}
		}	
}

tarefa Cropagem{FunAtua()
	se(senEsqL > 168)entao{senEsqL = 168}
	se(senDirL > 168)entao{senDirL = 168}
}

tarefa seguirLinha(numero forca, numero referencia){
	Cropagem()
	senEsqL = (senEsqL - referencia)
	senDirL = (senDirL - referencia)
	se(senCenL > 3)entao{senCenL = 3}
	erro = (senEsqL - senDirL)*senCenL
	Motor("lmotor", forca + erro)
	Motor("rmotor", forca - erro)
	Motor("lmotorTras", (forca + erro))
	Motor("rmotorTras", (forca - erro))
}

tarefa ViObstaculo{FunAtua()
	se(senUltraF < 2.5 e senUltraF > 0)entao{FunAtua()
		enquanto(senultraL > 6 ou (senUltraF < 3 e senUltraF > 0) ou senultraL < 0)farei{
			DireitaEixoRobo(500)
			Esperar(50)
		}
		farei{             
			Frente(100)
			Esperar(40) #50
			EsquerdaEixoRoda(1000)
			Esperar(80)
		}enquanto(senCen != "Preto" e senEsq != "Preto" e senEsqEx != "Preto" e senDirEx != "Preto" e senDir != "Preto")
				Frente(100)
				Esperar(200)
				FunAtua()
			se(senCen != "Preto" e senEsq != "Preto" e senEsqEx != "Preto" e senDirEx != "Preto" e senDir != "Preto")entao{
				enquanto(senCen != "Preto")farei{
					ProcurarLinha()
					Esperar(50)
				}
			}Tras(100)
		Esperar(200)
	}
}

tarefa curvaNoventa{FunAtua()
	se(senDirEx == "Preto" e senEsqEx == "Branco")entao{
		Frente(200)
		Esperar(350)
		ProcurarLinha()
		Frente(200)
		Esperar(500)
	}senao{FunAtua()
		se(senEsqEx == "Preto" e senDirEx == "Branco")entao{	
				Frente(200)
				Esperar(350)
				ProcurarLinha(falso)
				Frente(200)
				Esperar(500)
			}senao{FunAtua()
				se(senDirEx == "Preto" e senEsqEx == "Preto")entao{
					Frente(200)
					Esperar(550)
				}senao{
					seguirLinha(160,150)
					AcheiVerde()
					ViObstaculo()
				}
			}
	}
}

tarefa Aceleracao{ #Variando a velocidade de ir para frente de acordo com a inclinação do robô
	FunAtua()
	IdentificarSalaDeResgate()
	se((Inclinacao() > 300 ) e (Inclinacao() < 357))entao{
		Frente(200)
		Esperar(50)
		seguirLinha(160,150)
	}senao se((Inclinacao() > 8 ) e (Inclinacao() < 300))entao{
				Frente(50)
				seguirLinha(160,150)
			}senao{curvaNoventa()}
}

tarefa PegarKit{
	Tras(1000)
	Esperar(20)
	PararMotor()
	InclinarGarrinha(0-200)
	AbrirGarrinha(0-200)
	InclinarGarrinha(0-100)
	MoverGarrinha(200)			
	AbrirGarrinha(210)
	InclinarGarrinha(100)
	MoverGarrinha(0-290)	
	PararMotor(falso)
}

inicio
	Frente(1)	#Ativando os motores 
	InclinarGarrinha(200)
	enquanto(!viVermelho) farei{ #LevantarAtuador	
		se(naoAcheiSalaResgate)entao{Aceleracao()
			se(Toque("senToque"))entao{PegarKit()}
		}senao{
			ProcurarAreaDeResgate()
			VerificarVermelho()
		} Esperar(60) #evita o sbotics crashar 
	} PararMotor()
fim