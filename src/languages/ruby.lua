local L = {}

L.lexer = "ruby"

L.singleLineComment = "# "

L.extensions = {
	"rb",
	"rbw",
}

L.keywords = {
	[0] = "ARGF ARGV BEGIN END ENV FALSE DATA NIL RUBY_PATCHLEVEL RUBY_PLATFORM RUBY_RELEASE_DATE RUBY_VERSION PLATFORM RELEASE_DATE STDERR STDIN STDOUT TOPLEVEL_BINDING TRUE __ENCODING__ __END__ __FILE__ __LINE__ alias and begin break case class def defined? do else elsif end ensure false for if in module next nil not or redo rescue retry return self super then true undef unless until when while yield",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["ERROR"] = {
		id = 1,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENTLINE"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["POD"] = {
		id = 3,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1E3320),
	},
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["INSTRUCTION"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["STRING"] = {
		id = 6,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER"] = {
		id = 7,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["CLASS NAME"] = {
		id = 8,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["DEF NAME"] = {
		id = 9,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["IDENTIFIER"] = {
		id = 11,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["REGEX"] = {
		id = 12,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["GLOBAL"] = {
		id = 13,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["SYMBOL"] = {
		id = 14,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["MODULE NAME"] = {
		id = 15,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["INSTANCE VAR"] = {
		id = 16,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["CLASS VAR"] = {
		id = 17,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["BACKTICKS"] = {
		id = 18,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x2D1E1E),
	},
	["DATA SECTION"] = {
		id = 19,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1E1E1E),
	},
	["STRING Q"] = {
		id = 24,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
}
return L
