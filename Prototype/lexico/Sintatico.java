package sintatico;

import java.io.IOException;

import lexico.*;

public class Sintatico {
	public Token lookahed;
	public Analisador lexico;
	
	public Sintatico(String arquivo) throws IOException {
		lexico = new Analisador();
		lexico.abreArquivo(arquivo);
	}
	
	public void analise() {
		lookahed = lexico.capturaToken();
		P();
		E();
		consumir(TipoToken.EOF);
		System.out.println("Análise Finalizada");
	}

	private void P() {
		
		consumir(TipoToken.IDTIPO);
		consumir(TipoToken.IDVAR);
	}

	private void E() {
		//if(lookahed.getToken() == TipoToken.IDVAR || lookahed.getToken() == TipoToken.OPIGUAL) {
			consumir(TipoToken.IDVAR);
			if(lookahed.getToken() == TipoToken.OPIGUAL)
					Operadores();
			if(lookahed.getToken() == TipoToken.EOF);
			else	erro();
		}
		
	

	private void Operadores() {
		consumir(TipoToken.OPIGUAL);
		if(lookahed.getToken() == TipoToken.IDVAR)
			E();
		else
			erro();
	}

	private void consumir(TipoToken token) {
		if(lookahed.getToken() == token)
			lookahed = lexico.capturaToken();
		else {
			System.err.println("Erro na linha "+lookahed.getLinha());
			System.err.println("Esperava "+lookahed.getToken());
		}
		
	}
	
	private void erro() {
		System.err.println("Erro sintatico linha: "+lookahed.getLinha());
	}
	
	public static void main(String[] args) throws IOException {
		Sintatico sintatico = new Sintatico("teste.txt");
		sintatico.analise();
	}
}
