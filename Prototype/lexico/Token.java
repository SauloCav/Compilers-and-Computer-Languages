package lexico;

public class Token {
	private TipoToken token;
	private String lexema;
	private int linha;
	
	
	public Token(TipoToken token, String lexema, int linha) {
		super();
		this.token = token;
		this.lexema = lexema;
		this.linha = linha;
	}
	public TipoToken getToken() {
		return token;
	}
	public void setToken(TipoToken token) {
		this.token = token;
	}
	public String getLexema() {
		return lexema;
	}
	public void setLexema(String lexema) {
		this.lexema = lexema;
	}
	public int getLinha() {
		return linha;
	}
	public void setLinha(int linha) {
		this.linha = linha;
	}
	@Override
	public String toString() {
		return "Token [token=" + token + ", lexema=" + lexema + ", linha=" + linha + "]";
	}
	
	
	
}
