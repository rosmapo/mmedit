local L = {}

L.lexer = "rust"

L.singleLineComment = "// "

L.extensions = {
	"rs",
}

L.keywords = {
	[0] = "abstract as async become box break const continue crate do dyn else enum extern false final fn for if impl in let loop macro match mod move mut override priv pub ref return self static struct super trait true try type typeof unsafe unsized use virtual where while yield",
	[1] = "bool char f32 f64 i128 i16 i32 i64 i8 isize str u128 u16 u32 u64 u8 usize",
	[2] = "Self",
	[3] = "None",
	[4] = "None",
	[5] = "None",
	[6] = "None",
}

L.styles = {
	["DEFAULT"] = {
		id = 32,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["WHITESPACE"] = {
		id = 0,
		fgColor = rgb(0x858585),
		bgColor = rgb(0x1F1F1F),
	},
	["BLOCK COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["LINE COMMENT"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["BLOCK DOC COMMENT"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["LINE DOC COMMENT"] = {
		id = 4,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 5,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["KEYWORDS 1"] = {
		id = 6,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["KEYWORDS 2"] = {
		id = 7,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["KEYWORDS 3"] = {
		id = 8,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["KEYWORDS 4"] = {
		id = 9,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["KEYWORDS 5"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["KEYWORDS 6"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["KEYWORDS 7"] = {
		id = 12,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["REGULAR STRING"] = {
		id = 13,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["RAW STRING"] = {
		id = 14,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["CHARACTER"] = {
		id = 15,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["OPERATOR"] = {
		id = 16,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 17,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
	},
	["LIFETIME"] = {
		id = 18,
		fgColor = rgb(0x4EC9B0),
		bgColor = rgb(0x1F1F1F),
	},
	["MACRO"] = {
		id = 19,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x1F1F1F),
	},
	["LEXICAL ERROR"] = {
		id = 20,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x251825),
	},
	["BYTE STRING"] = {
		id = 21,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["RAW BYTE STRING"] = {
		id = 22,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
	["BYTE CHARACTER"] = {
		id = 23,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
	},
}
return L
