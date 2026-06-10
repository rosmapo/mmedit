local L = {}

L.lexer = "nimrod"

L.singleLineComment = "! "

L.extensions = {
	"nim",
}

L.keywords = {
	[0] = "addr and as asm block break case cast const continue converter discard div elif else end enum except exception finally for from generic if implies import in include is isnot iterator lambda macro method mod nil not notin object of or out proc ptr raise ref return shl shr template try tuple type var when where while with without xor yield",
}

L.styles = {
	["WHITE SPACE"] = {
		id = 0,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 2,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING"] = {
		id = 3,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["SINGLE QUOTED STRING"] = {
		id = 4,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["KEYWORD"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["TRIPLE QUOTES"] = {
		id = 6,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["TRIPLE DOUBLE QUOTES"] = {
		id = 7,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["CLASS NAME DEFINITION"] = {
		id = 8,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["FUNCTION OR METHOD NAME DEFINITION"] = {
		id = 9,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["OPERATORS"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["IDENTIFIERS"] = {
		id = 11,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT-BLOCKS"] = {
		id = 12,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["END OF LINE WHERE STRING IS NOT CLOSED"] = {
		id = 13,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x251825),
	},
	["HIGHLIGHTED IDENTIFIERS"] = {
		id = 14,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0x1F1F1F),
	},
	["DECORATORS"] = {
		id = 15,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
