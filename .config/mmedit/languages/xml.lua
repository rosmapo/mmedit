local L = {}

L.lexer = "xml"

L.first_line = {
	"^<%?xml"
}

L.extensions = {
	"xml",
	"xaml",
	"xsl",
	"xslt",
	"xsd",
	"xul",
	"kml",
	"svg",
	"mxml",
	"xsml",
	"wsdl",
	"xlf",
	"xliff",
	"xbl",
	"sxbl",
	"sitemap",
	"gml",
	"gpx",
	"plist",
	"vcproj",
	"vcxproj",
	"csproj",
	"csxproj",
	"vbproj",
	"dbproj",
}

L.properties = {
	["fold.html"] = "1",
}

L.keywords = {
}

L.styles = {
	["XMLSTART"] = {
		id = 12,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x2D2D00),
	},
	["XMLEND"] = {
		id = 13,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x2D2D00),
	},
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["COMMENT"] = {
		id = 9,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0x1F1F1F),
	},
	["NUMBER"] = {
		id = 5,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["DOUBLESTRING"] = {
		id = 6,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["SINGLESTRING"] = {
		id = 7,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0x1F1F1F),
		fontStyle = 1,
	},
	["TAG"] = {
		id = 1,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["TAGEND"] = {
		id = 11,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["TAGUNKNOWN"] = {
		id = 2,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0x1F1F1F),
	},
	["ATTRIBUTE"] = {
		id = 3,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["ATTRIBUTEUNKNOWN"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0x1F1F1F),
	},
	["SGMLDEFAULT"] = {
		id = 21,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1E2840),
	},
	["CDATA"] = {
		id = 17,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0x1F1F1F),
	},
	["ENTITY"] = {
		id = 10,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0x1E1E1E),
		fontStyle = 2,
	},
}
return L
