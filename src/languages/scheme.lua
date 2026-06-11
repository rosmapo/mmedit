local L = {}

L.lexer = "scheme"

L.singleLineComment = "; "

L.extensions = {
	"scm",
	"smd",
	"ss",
}

L.keywords = {
	[0] = "+ - * / = < > <= >= => abs acos and angle append apply asin assoc assq assv atan begin boolean? caar cadr call-with-current-continuation call/cc call-with-input-file call-with-output-file call-with-values car cdr cdar cddr caaar caadr cadar caddr cdaar cdadr cddar cdddr caaaar caaadr caadar caaddr cadaar cadadr caddar cadddr cdaaar cdaadr cdadar cdaddr cddaar cddadr cdddar cddddr case ceiling char->integer char-alphabetic? char-ci<=? char-ci<? char-ci=? char-ci>=? char-ci>? char-downcase char-lower-case? char-numeric? char-ready? char-upcase char-upper-case? char-whitespace? char<=? char<? char=? char>=? char>? char? close-input-port close-output-port complex? cond cons cos current-input-port current-output-port define define-syntax delay denominator display do dynamic-wind else eof-object? eq? equal? eqv? eval even? exact->inexact exact? exp expt floor for-each force gcd if imag-part inexact->exact inexact? input-port? integer->char integer? interaction-environment lambda lcm length let let* let-syntax letrec letrec-syntax list list->string list->vector list-ref list-tail list? load log magnitude make-polar make-rectangular make-string make-vector map max member memq memv min modulo negative? newline not null-environment null? number->string number? numerator odd? open-input-file open-output-file or output-port? pair? peek-char positive? procedure? quasiquote quote quotient rational? rationalize read read-char real-part real? remainder reverse round scheme-report-environment set! set-car! set-cdr! sin sqrt string string->list string->number string->symbol string-append string-ci<=? string-ci<? string-ci=? string-ci>=? string-ci>? string-copy string-fill! string-length string-ref string-set! string<=? string<? string=? string>=? string>? string? substring symbol->string symbol? syntax-rules transcript-off transcript-on truncate unquote unquote-splicing values vector vector->list vector-fill! vector-length vector-ref vector-set! vector? with-input-from-file with-output-to-file write write-char zero?",
	[1] = "None",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENTLINE"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 2,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["FUNCTION WORD"] = {
		id = 3,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["FUNCTION WORD2"] = {
		id = 4,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["SYMBOL"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["STRING"] = {
		id = 6,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["IDENTIFIER"] = {
		id = 9,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["SPECIAL"] = {
		id = 11,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT"] = {
		id = 12,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
