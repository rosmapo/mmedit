local L = {}

L.lexer = "lua"

L.singleLineComment = "-- "

L.extensions = {
	"lua",
}

L.keywords = {
	[0] = "and break do else elseif end false for function goto if in local nil not or repeat return then true until while",
	[1] = "_ENV _G _VERSION assert collectgarbage dofile error getfenv getmetatable ipairs load loadfile loadstring module next pairs pcall print rawequal rawget rawlen rawset require select setfenv setmetatable tonumber tostring type unpack xpcall string table math bit32 coroutine io os debug package __index __newindex __call __add __sub __mul __div __mod __pow __unm __concat __len __eq __lt __le __gc __mode",
	[2] = "byte char dump find format gmatch gsub len lower match rep reverse sub upper abs acos asin atan atan2 ceil cos cosh deg exp floor fmod frexp ldexp log log10 max min modf pow rad random randomseed sin sinh sqrt tan tanh arshift band bnot bor btest bxor extract lrotate lshift replace rrotate rshift shift string.byte string.char string.dump string.find string.format string.gmatch string.gsub string.len string.lower string.match string.rep string.reverse string.sub string.upper table.concat table.insert table.maxn table.pack table.remove table.sort table.unpack math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.cosh math.deg math.exp math.floor math.fmod math.frexp math.huge math.ldexp math.log math.log10 math.max math.min math.modf math.pi math.pow math.rad math.random math.randomseed math.sin math.sinh math.sqrt math.tan math.tanh bit32.arshift bit32.band bit32.bnot bit32.bor bit32.btest bit32.bxor bit32.extract bit32.lrotate bit32.lshift bit32.replace bit32.rrotate bit32.rshift",
	[3] = "close flush lines read seek setvbuf write clock date difftime execute exit getenv remove rename setlocale time tmpname coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap coroutine.yield io.close io.flush io.input io.lines io.open io.output io.popen io.read io.tmpfile io.type io.write io.stderr io.stdin io.stdout os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale os.time os.tmpname debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable debug.getregistry debug.getupvalue debug.getuservalue debug.setfenv debug.sethook debug.setlocal debug.setmetatable debug.setupvalue debug.setuservalue debug.traceback debug.upvalueid debug.upvaluejoin package.cpath package.loaded package.loaders package.loadlib package.path package.preload package.seeall",
}

L.styles = {
	-- Plain text
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),  -- light grey
		bgColor = rgb(0xFFFFFF),
	},
	-- Block comments --[[ ... ]]
	["COMMENT"] = {
		id = 1,
		fgColor = rgb(0x6A9955),  -- green (VSCode comment)
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,             -- italic
	},
	-- Line comments -- ...
	["COMMENT LINE"] = {
		id = 2,
		fgColor = rgb(0x6A9955),  -- green
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,             -- italic
	},
	-- Doc comments ---
	["COMMENT DOC"] = {
		id = 3,
		fgColor = rgb(0x6A9955),  -- green, same family
		bgColor = rgb(0xFFFFFF),
		fontStyle = 2,
	},
	-- Numbers: 42, 3.14, 0xFF
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xD7BA7D),  -- gold (VSCode number)
		bgColor = rgb(0xFFFFFF),
	},
	-- Keywords: if, then, end, for, function...
	["INSTRUCTION WORD"] = {
		id = 5,
		fgColor = rgb(0x569CD6),  -- blue (VSCode keyword)
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,             -- bold
	},
	-- Double-quoted strings "..."
	["STRING"] = {
		id = 6,
		fgColor = rgb(0xCE9178),  -- orange (VSCode string)
		bgColor = rgb(0xFFFFFF),
	},
	-- Single-quoted strings '...'
	["CHARACTER"] = {
		id = 7,
		fgColor = rgb(0xCE9178),  -- orange
		bgColor = rgb(0xFFFFFF),
	},
	-- Long strings [[ ... ]]
	["LITERALSTRING"] = {
		id = 8,
		fgColor = rgb(0xCE9178),  -- orange (same as strings)
		bgColor = rgb(0xFFFFFF),
	},
	-- Preprocessor / shebang
	["PREPROCESSOR"] = {
		id = 9,
		fgColor = rgb(0x569CD6),  -- blue
		bgColor = rgb(0xFFFFFF),
	},
	-- Operators: + - * / = ( ) [ ] { } , . : ;
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),  -- light grey (unobtrusive)
		bgColor = rgb(0xFFFFFF),
	},
	-- Identifiers: variable names, function names
	["IDENTIFIER"] = {
		id = 11,
		fgColor = rgb(0x9CDCFE),  -- light blue (VSCode variable)
		bgColor = rgb(0xFFFFFF),
	},
	-- Labels ::label::
	["LABEL"] = {
		id = 20,
		fgColor = rgb(0xD7BA7D),  -- gold
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	-- Built-in functions (keyword set 1): print, pairs, ipairs, require...
	["FUNC1"] = {
		id = 13,
		fgColor = rgb(0x4EC9B0),  -- teal (VSCode built-in type/function)
		bgColor = rgb(0xFFFFFF),
	},
	-- Standard library methods (keyword set 2): string.format, math.floor...
	["FUNC2"] = {
		id = 14,
		fgColor = rgb(0x4FC1FF),  -- bright cyan (VSCode method)
		bgColor = rgb(0xFFFFFF),
	},
	-- Extended library (keyword set 3): io, os, debug...
	["FUNC3"] = {
		id = 15,
		fgColor = rgb(0x4EC9B0),  -- teal
		bgColor = rgb(0xFFFFFF),
	},
}
return L
