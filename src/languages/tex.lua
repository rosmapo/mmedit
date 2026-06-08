local L = {}

L.lexer = "tex"

L.singleLineComment = "% "

L.extensions = {
	"tex",
}

L.keywords = {
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["SPECIAL"] = {
		id = 1,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["GROUP"] = {
		id = 2,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["SYMBOL"] = {
		id = 3,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMAND"] = {
		id = 4,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["TEXT"] = {
		id = 5,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
