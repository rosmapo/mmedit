local L = {}

L.lexer = "pascal"

L.singleLineComment = "// "

L.extensions = {
	"pas",
	"pp",
	"p",
	"inc",
	"lpr",
}

L.keywords = {
	[0] = "and array asm begin case cdecl class const constructor default destructor div do downto else end end. except exit exports external far file finalization finally for function goto if implementation in index inherited initialization inline interface label library message mod near nil not object of on or out overload override packed pascal private procedure program property protected public published raise read record register repeat resourcestring safecall set shl shr stdcall stored string then threadvar to try type unit until uses var virtual while with write xor",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["IDENTIFIER"] = {
		id = 1,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT LINE"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT DOC"] = {
		id = 4,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR"] = {
		id = 5,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR2"] = {
		id = 6,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 7,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["HEX NUMBER"] = {
		id = 8,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["INSTRUCTION WORD"] = {
		id = 9,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["STRING"] = {
		id = 10,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 12,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 13,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["ASM"] = {
		id = 14,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
}
return L
