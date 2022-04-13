package lexico;

public class Simbolos {
	public static boolean verificaSimbolo(char c) {
		if( c=='+' || c == '-' || c == '<'|| c == '\n'
				|| c=='/' || c==' '|| c == '>'
				|| c == '\n'|| c == '\t')
			return true;
		return false;
	}
}
