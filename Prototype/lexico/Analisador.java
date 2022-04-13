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
    	if(linha==null) return 0;//caso a primeira linha lida ao abrir o arquivo seja nula
    	if(posicaoLinha == linha.length()) {//se já leu todos os caracteres
    		try {
				linha = arquivo.readLine();//busca-se uma nova linha
			} catch (IOException e) {
				e.printStackTrace();
			}
    		if(linha == null)//final do arquivo
    		{
                numeroLinha++;
                return 0;
            }
    		else {//tem linha nova
    			linha = linha.concat("\n");
                numeroLinha++;
                posicaoLinha = 0;
    		}
    	}
    	char ch = linha.charAt(posicaoLinha);//ler o primeiro caracter
        posicaoLinha++;//incrementa a posição
        return ch;//retorna esse caracter
    }
    public boolean proximoChar(char c) {//compara um caracter recebido com o próximo a ser lido
    	char proximo = getChar();
    	return c==proximo;
    }
    
    public Token capturaToken() {
    	Token token = null;
    	Automato automato = Automato.OPERADOR;
    	String lexema = "";
    	char c;
    	while(token == null)//o processo garante o encontro de um token, nem que este seja EOF
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
	                    			posicaoLinha--;//retorna o caracter por conta do metodo proximo char
	                    			token = new Token(TipoToken.OPMAIOR, ">", numeroLinha);
	                    		}
	                    	}break;
	                    case '<':{
	                    	if(proximoChar('=')) 
                    			token = new Token(TipoToken.OPMENORIGUAL, "<=", numeroLinha);
                    		else{
                    			posicaoLinha--;//retornar um caracter de leitura por conta do metodo proximo char
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
                	if(Simbolos.verificaSimbolo(c)) {//verifica se é um lexema já pronto
                		switch (lexema) {
						case "int": {
							token = new Token(TipoToken.IDTIPO, lexema, numeroLinha);
						}break;
						default:
							token = new Token(TipoToken.IDVAR, lexema, numeroLinha);
						}//switch lexema
                	}//if
                	else {
                		if(Character.isLetter(c) || c == '_')
                			lexema +=c;
                	}
            }//switch autômato
        }//while
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

	    


