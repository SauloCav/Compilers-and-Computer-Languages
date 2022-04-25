package lexico;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
/**
 * 
 * Este analisador faz uso de elementos do projeto de arthurmteodoro (ano 2017) 
 * e notas de aula do Prof. Andrei Formiga (ano 2010)
 *
 */
public class Analisador {

		private BufferedReader arquivo;
	    private String arquivoNome;
	    private String linha;
	    private int numeroLinha;
	    private int posicaoLinha;
	    
    public void abreArquivo(String nomeArquivo) throws IOException {
    	arquivo = new BufferedReader(new FileReader(nomeArquivo));
    	arquivoNome = nomeArquivo;
    	linha = arquivo.readLine().concat("\n");
    	numeroLinha=1;
    	posicaoLinha=0;
    }
    public void fechaArquivo(String nomeArquivo) throws IOException {
    	arquivo.close();
    	linha="";
    	this.numeroLinha = 0;
        this.posicaoLinha = 0;
    }
    public char getChar() {
    	if(linha==null) return 0;
    	if(posicaoLinha == linha.length()) {
    		try {
				linha = arquivo.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
    		if(linha == null)
    		{
                numeroLinha++;
                return 0;
            }
    		else {
    			linha = linha.concat("\n");
                numeroLinha++;
                posicaoLinha = 0;
    		}
    	}
    	char ch = linha.charAt(posicaoLinha);
        posicaoLinha++;
        return ch;
    }
    public boolean proximoChar(char c) {
    	char proximo = getChar();
    	return c==proximo;
    }
    
    public Token capturaToken() {
    	Token token = null;
    	Automato automato = Automato.OPERADOR;
    	String lexema = "";
    	char c;
    	while(token == null)
        {
            switch(automato)
            {
                case OPERADOR:
                    c = getChar();
                    switch(c)
                    {
	                    case '>':{
	                    		if(proximoChar('=')) 
	                    			token = new Token(TipoToken.OPMAIORIGUAL, ">=", numeroLinha);
	                    		else{
	                    			posicaoLinha--;
	                    			token = new Token(TipoToken.OPMAIOR, ">", numeroLinha);
	                    		}
	                    	}break;
	                    case '<':{
	                    	if(proximoChar('=')) 
                    			token = new Token(TipoToken.OPMENORIGUAL, "<=", numeroLinha);
                    		else{
                    			posicaoLinha--;
                    			token = new Token(TipoToken.OPMENOR, "<", numeroLinha);
                    		}
	                    }break;
	                    case '=':{
	                    	if(proximoChar('='))
	                    		token = new Token(TipoToken.OPIGUAL, "==", numeroLinha);
	                    }break;
	                    default:{
	                    	if(c==0)
	                    		token = new Token(TipoToken.EOF, "erro fim do arquivo", numeroLinha);
	                    	else
	                    		if(Character.isLetter(c)) {
	                    			automato = Automato.IDENTIFICADOR;
	                    			lexema +=c;
	                    		}
	                    }break;
                    }break;//switch caracter
                case IDENTIFICADOR:
                	c = getChar();
                	if(Simbolos.verificaSimbolo(c)) {
                		switch (lexema) {
						case "int": {
							token = new Token(TipoToken.IDTIPO, lexema, numeroLinha);
						}break;
						default:
							token = new Token(TipoToken.IDVAR, lexema, numeroLinha);
						}
                	}
                	else {
                		if(Character.isLetter(c) || c == '_')
                			lexema +=c;
                	}
            }
        }
    	return token;
    }
    public static void main(String[] args) {
		Analisador lexico = new Analisador();
		Token token;
		try {
			lexico.abreArquivo("teste.txt");
			token = lexico.capturaToken();
			while (token.getToken() != TipoToken.EOF) {
				System.out.println(token.toString());
				token = lexico.capturaToken();
			}
			System.out.println(token.toString());
			lexico.fechaArquivo("teste.txt");
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
