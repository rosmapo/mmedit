local L = {}

L.lexer = "haskell"

L.singleLineComment = "-- "

L.extensions = {
	"hs",
	"lhs",
	"las",
}

L.keywords = {
	[0] = "as case class data default deriving do else hiding if import in infix infixl infixr instance let module newtype of proc qualified rec then type where _",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["IDENTIFIER"] = {
		id = 1,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["KEYWORD"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["NUMBER"] = {
		id = 3,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 5,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["CLASS"] = {
		id = 6,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["MODULE"] = {
		id = 7,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["CAPITAL"] = {
		id = 8,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["DATA"] = {
		id = 9,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["IMPORT"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["INSTANCE"] = {
		id = 12,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENTLINE"] = {
		id = 13,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENTBLOCK"] = {
		id = 14,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENTBLOCK2"] = {
		id = 15,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENTBLOCK3"] = {
		id = 16,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
