local L = {}

L.lexer = "visualprolog"

L.singleLineComment = "% "

L.extensions = {
	"pro",
	"cl",
	"i",
	"pack",
	"ph",
}

L.keywords = {
	[0] = "goal namespace interface class implement open inherits supports resolve delegate monitor constants domains predicates constructors properties clauses facts",
	[1] = "guard language stdcall apicall c thiscall prolog digits if then elseif else foreach do try catch finally erroneous failure procedure determ multi nondeterm anyflow and or externally from div mod rem quot in orelse otherwise",
	[2] = "include bininclude requires orrequires if then else elseif endif error message export externally options",
	[3] = "short detail end exception withdomain",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["MAJOR"] = {
		id = 1,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0xFFFFFF),
	},
	["MINOR"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["DIRECTIVE"] = {
		id = 3,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT BLOCK"] = {
		id = 4,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT LINE"] = {
		id = 5,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT KEY"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT KEY ERROR"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["IDENTIFIER"] = {
		id = 8,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["VARIABLE"] = {
		id = 9,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["ANONYMOUS"] = {
		id = 10,
		fgColor = rgb(0x9090B0),
		bgColor = rgb(0xFFFFFF),
	},
	["NUMBER"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
	},
	["OPERATOR"] = {
		id = 12,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER"] = {
		id = 13,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER TOO MANY"] = {
		id = 14,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER ESCAPE ERROR"] = {
		id = 15,
		fgColor = rgb(0xFFA0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 16,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING ESCAPE"] = {
		id = 17,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING ESCAPE ERROR"] = {
		id = 18,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING EOL OPEN"] = {
		id = 19,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x3D0000),
	},
	["STRING VERBATIM"] = {
		id = 20,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING VERBATIM SPECIAL"] = {
		id = 21,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING VERBATIM EOL"] = {
		id = 22,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x2D1800),
	},
}
return L
