local L = {}

L.lexer = "batch"

L.singleLineComment = "REM "

L.extensions = {
	"bat",
	"cmd",
	"nt",
}

L.keywords = {
	[0] = "assoc aux break call cd chcp chdir choice cls cmdextversion color com com1 com2 com3 com4 con copy country ctty date defined del dir do dpath echo else endlocal erase errorlevel exist exit for ftype goto if in loadfix loadhigh lpt lpt1 lpt2 lpt3 lpt4 md mkdir move not nul path pause popd prn prompt pushd rd rem ren rename rmdir set setlocal shift start time title type ver verify vol",
}

L.styles = {
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["KEYWORDS"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["LABEL"] = {
		id = 3,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["HIDE SYMBOL"] = {
		id = 4,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["COMMAND"] = {
		id = 5,
		fgColor = rgb(0x4FC1FF),
		bgColor = rgb(0xFFFFFF),
	},
	["VARIABLE"] = {
		id = 6,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 1,
	},
	["OPERATOR"] = {
		id = 7,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
}
return L
