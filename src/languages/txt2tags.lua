local L = {}

L.lexer = "txt2tags"

L.singleLineComment = "! "

L.extensions = {
	"t2t",
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
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["STRONG"] = {
		id = 2,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["STRONG 2 (NOT USED)"] = {
		id = 3,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["EM1 (ITALIC)"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	["EM2 (UNDERLINE)"] = {
		id = 5,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["H1"] = {
		id = 6,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["H2"] = {
		id = 7,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["H3"] = {
		id = 8,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["H4"] = {
		id = 9,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["H5"] = {
		id = 10,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["H6"] = {
		id = 11,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["PRECHAR (NOT USED)"] = {
		id = 12,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["ULIST"] = {
		id = 13,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["OLIST"] = {
		id = 14,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["BLOCKQUOTE"] = {
		id = 15,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0xFFFFFF),
	},
	["STRIKEOUT"] = {
		id = 16,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["HRULE"] = {
		id = 17,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["LINK"] = {
		id = 18,
		fgColor = rgb(0xA9D0FF),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	["CODE"] = {
		id = 19,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["CODE2"] = {
		id = 20,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["CODEBLOCK"] = {
		id = 21,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT"] = {
		id = 22,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["OPTION"] = {
		id = 23,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["PREPROC"] = {
		id = 24,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["POSTPROC"] = {
		id = 25,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
