local L = {}

L.lexer = "cpp"

L.singleLineComment = "// "

L.extensions = {
	"cs",
}

L.keywords = {
	[0] = "abstract add alias as ascending async await base break case catch checked continue default delegate descending do dynamic else event explicit extern false finally fixed for foreach from get global goto group if implicit in interface internal into is join let lock namespace new null object operator orderby out override params partial private protected public readonly ref remove return sealed select set sizeof stackalloc switch this throw true try typeof unchecked unsafe using value virtual where while yield",
	[1] = "bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort var void",
}

L.styles = {
	["PREPROCESSOR"] = {
		id = 9,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0x1F1F1F),
	},
	["DEFAULT"] = {
		id = 11,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["INSTRUCTION WORD"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["TYPE WORD"] = {
		id = 16,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["STRING"] = {
		id = 6,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["VERBATIM"] = {
		id = 13,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["REGEX"] = {
		id = 14,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT LINE"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT DOC"] = {
		id = 3,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT LINE DOC"] = {
		id = 15,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["COMMENT DOC KEYWORD"] = {
		id = 17,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["COMMENT DOC KEYWORD ERROR"] = {
		id = 18,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR COMMENT"] = {
		id = 23,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["PREPROCESSOR COMMENT DOC"] = {
		id = 24,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
