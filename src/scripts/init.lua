function rgb(x)
    return ((x & 0xFF) << 16) | (x & 0xFF00) | ((x & 0xFF0000) >> 16)
end

-- ============================================================
-- Theme support (dark / light)
-- ============================================================
--
-- The language files define their colors using the VS Code "Dark+"
-- palette via rgb(0xRRGGBB) calls (the rgb() helper above converts
-- the RGB hex constant into the BGR order Scintilla expects).
--
-- To support a light theme without touching every language file,
-- every dark color used across the language definitions is mapped
-- here to its VS Code "Light+" equivalent. SetStyle() looks up each
-- fgColor/bgColor in this map (when dark_mode is false) and
-- substitutes the light equivalent before handing it to Scintilla.

-- dark_mode defaults to true (matches the previous hardcoded theme).
-- The C++ side overrides this global from ApplicationSettings before
-- (re)applying the language/theme to an editor.
if dark_mode == nil then
    dark_mode = true
end

-- Dark (VS Code Dark+) hex -> Light (VS Code Light+) hex, in normal
-- RGB order. Both sides are passed through rgb() below so the table
-- ends up keyed/valued in the BGR order that style.fgColor /
-- style.bgColor are already stored in.
local light_equivalents_rgb = {
    [0x1E1E1E] = 0xFFFFFF, -- editor background
    [0x1F1F1F] = 0xFFFFFF, -- general background used by most styles
    [0xD4D4D4] = 0x000000, -- default foreground text
    [0x569CD6] = 0x0000FF, -- keyword blue
    [0x6A9955] = 0x008000, -- comment green
    [0xC586C0] = 0xAF00DB, -- control keyword / type purple
    [0x4EC9B0] = 0x267F99, -- type / class teal
    [0x858585] = 0x919191, -- muted grey (comments, line number fg)
    [0xF44747] = 0xE51400, -- error red
    [0xCE9178] = 0xA31515, -- string orange
    [0xD7BA7D] = 0x811F3F, -- escape sequence / regex tan
    [0x4FC1FF] = 0x001080, -- variable cyan
    [0xFFE0A0] = 0x800000, -- preprocessor tan
    [0x9CDCFE] = 0x001080, -- property / parameter light blue
    [0x3D0000] = 0xFFC0CB, -- dark red error background
    [0xFFA0A0] = 0xCD3131, -- light red foreground (on dark bg)
    [0x1E2D2D] = 0xE0F0F0, -- dark teal background variant
    [0xDCDCAA] = 0x795E26, -- function name yellow
    [0x2D2D2D] = 0xF3F3F3, -- slightly lighter background variant
    [0x3C3C3C] = 0xEEEEEE, -- lighter background variant
    [0x2D2D00] = 0xFFFFE0, -- olive background
    [0x251825] = 0xF5E6F5, -- plum background
    [0xA0A0A0] = 0x6E6E6E, -- mid grey
    [0x2D002D] = 0xFCE8FC, -- dark magenta background
    [0x1E3320] = 0xE3F2E3, -- dark green background
    [0xB5CEA8] = 0x098658, -- number green
    [0xCA84F9] = 0x9B30C9, -- light purple
    [0xD16969] = 0xA31515, -- salmon red
    [0xA9D0FF] = 0x0451A5, -- light blue
    [0x9090B0] = 0x5C5C8A, -- muted blue-grey
    [0x2D2000] = 0xFFF4E0, -- brown background
    [0x2D1E1E] = 0xF5EDE5, -- dark brownish background
    [0x2D1800] = 0xFFF0DC, -- darker brown background
    [0x1E2840] = 0xE6EEF8, -- dark blue background
    [0x1E2820] = 0xE6F0E6, -- dark green-grey background
    [0x003333] = 0xE0F5F5, -- dark cyan background
    [0x2B2B2B] = 0xF3F3F3, -- line number margin background
}

-- Build the lookup table keyed/valued in Scintilla's BGR order, since
-- that's the form style.fgColor / style.bgColor are stored in.
palette_dark_to_light = {}
for darkRGB, lightRGB in pairs(light_equivalents_rgb) do
    palette_dark_to_light[rgb(darkRGB)] = rgb(lightRGB)
end

-- Returns the color to use for the given style color, taking the
-- current dark_mode setting into account. Colors are returned
-- unchanged in dark mode, and substituted with their light
-- equivalent (if known) in light mode.
function MapColor(color)
    if dark_mode then
        return color
    end

    return palette_dark_to_light[color] or color
end

-- Applies the editor-wide theme colors (STYLE_DEFAULT and the line
-- number margin) based on the current dark_mode setting. Called from
-- SetLanguage() so every language switch -- and every re-application
-- triggered by toggling Dark Mode -- uses the correct palette.
function ApplyTheme()
    if dark_mode then
        editor.StyleFore[32] = rgb(0xD4D4D4) -- STYLE_DEFAULT fg: light grey text
        editor.StyleBack[32] = rgb(0x1E1E1E) -- STYLE_DEFAULT bg: dark background
        editor:StyleClearAll()                -- propagate STYLE_DEFAULT to all 256 styles

        editor.StyleFore[33] = rgb(0x858585) -- STYLE_LINENUMBER fg: muted grey
        editor.StyleBack[33] = rgb(0x2B2B2B) -- STYLE_LINENUMBER bg: slightly lighter than editor
    else
        editor.StyleFore[32] = rgb(0x000000) -- STYLE_DEFAULT fg: black text
        editor.StyleBack[32] = rgb(0xFFFFFF) -- STYLE_DEFAULT bg: white background
        editor:StyleClearAll()                -- propagate STYLE_DEFAULT to all 256 styles

        editor.StyleFore[33] = rgb(0x919191) -- STYLE_LINENUMBER fg: muted grey
        editor.StyleBack[33] = rgb(0xF3F3F3) -- STYLE_LINENUMBER bg: slightly darker than editor
    end
end

function DetectLanguageFromContents(contents)
    for name, L in pairs(languages) do
        if L.first_line then
            for _, pattern in ipairs(L.first_line) do
                if string.match(contents, pattern) then
                    return name
                end
            end
        end
    end
    return "Text"
end

function FilterForLanguage(name)
    local extensions = {}
    local language_definition = languages[name]

    if not language_definition.extensions then
        return nil
    end

    for _, ext in ipairs(language_definition.extensions) do
        if #ext > 0 then
            extensions[#extensions + 1] = "*." .. ext
        end
    end

    return  name .. " Files (" .. table.concat(extensions, " ") .. ")"
end

function DialogFilters()
    local filters = {}

    for name, L in pairs(languages) do
        local filter = FilterForLanguage(name)
        if filter then
            filters[#filters + 1] = filter
        end
    end

    table.sort(filters, function (a, b) return a:lower() < b:lower() end)
    table.insert(filters, 1, "All Files (*)")

    return table.concat(filters, ";;")
end

function SetStyle(L)
    if L.styles then
        for _, style in pairs(L.styles) do
            editor.StyleFore[style.id] = MapColor(style.fgColor)
            -- Skip white background (default) so STYLE_DEFAULT bg propagates
            if style.bgColor ~= 0xFFFFFF then
                editor.StyleBack[style.id] = MapColor(style.bgColor)
            end
            if style.fontStyle then
                editor.StyleBold[style.id] = (style.fontStyle & 1 == 1)
                editor.StyleItalic[style.id] = (style.fontStyle & 2 == 2)
                editor.StyleUnderline[style.id] = (style.fontStyle & 4 == 4)
                editor.StyleEOLFilled[style.id] = (style.fontStyle & 8 == 8)
            end
        end
    end

    if L.keywords then
        for id, kw in pairs(L.keywords) do
            editor.KeyWords[id] = kw
        end
    end

    if L.properties then
        for p, v in pairs(L.properties) do
            editor.Property[p] = v
        end
    end
end

function SetLanguage(languageName)
    local L = languages[languageName]

    if not skip_tabs then
        editor.UseTabs = (L.tabSettings or "tabs") == "tabs"
    end

    if not skip_tabwidth then
        editor.TabWidth = L.tabSize or 4
    end

    editor.MarginWidthN[2] = L.disableFoldMargin and 0 or 16

    -- Reset STYLE_DEFAULT (and the line number margin) to the current
    -- theme before applying language styles, then propagate it to all
    -- 256 styles via StyleClearAll().
    ApplyTheme()

    SetStyle(L)

    if L.additionalLanguages then
        for _, language in pairs(L.additionalLanguages) do
            SetStyle(languages[language])
        end
    end

    editor.Property["fold"] = "1"
    editor.Property["fold.compact"] = "0"
end

languages = {}
languages["ActionScript"] = require("actionscript")
languages["ADA"] = require("ada")
languages["Assembly"] = require("asm")
languages["ASN.1"] = require("asn1")
languages["asp"] = require("asp")
languages["autoIt"] = require("autoit")
languages["AviSynth"] = require("avs")
languages["BaanC"] = require("baanc")
languages["bash"] = require("bash")
languages["Batch"] = require("batch")
languages["BlitzBasic"] = require("blitzbasic")
languages["C"] = require("c")
languages["Caml"] = require("caml")
languages["CMakeFile"] = require("cmake")
languages["COBOL"] = require("cobol")
languages["Csound"] = require("csound")
languages["CoffeeScript"] = require("coffeescript")
languages["C++"] = require("cpp")
languages["C#"] = require("cs")
languages["CSS"] = require("css")
languages["SCSS"] = require("scss")
languages["D"] = require("d")
languages["DIFF"] = require("diff")
languages["Erlang"] = require("erlang")
languages["ESCRIPT"] = require("escript")
languages["Forth"] = require("forth")
languages["Fortran (free form)"] = require("fortran")
languages["Fortran (fixed form)"] = require("fortran77")
languages["FreeBasic"] = require("freebasic")
languages["GUI4CLI"] = require("gui4cli")
languages["Go"] = require("go")
languages["Haskell"] = require("haskell")
languages["HTML"] = require("html")
languages["ini file"] = require("ini")
languages["InnoSetup"] = require("inno")
languages["Intel HEX"] = require("ihex")
languages["Java"] = require("java")
languages["JavaScript"] = require("javascript")
languages["JSON"] = require("json")
languages["KiXtart"] = require("kix")
languages["LISP"] = require("lisp")
languages["LaTeX"] = require("latex")
languages["Lua"] = require("lua")
languages["Less"] = require("less")
languages["Makefile"] = require("makefile")
languages["Markdown"] = require("markdown")
languages["Matlab"] = require("matlab")
languages["MMIXAL"] = require("mmixal")
languages["Nimrod"] = require("nimrod")
languages["Nix"] = require("nix")
languages["extended crontab"] = require("nncrontab")
languages["Dos Style"] = require("nfo")
languages["NSIS"] = require("nsis")
languages["OScript"] = require("oscript")
languages["Objective-C"] = require("objc")
languages["Pascal"] = require("pascal")
languages["Perl"] = require("perl")
languages["PHP"] = require("php")
languages["Postscript"] = require("postscript")
languages["PowerShell"] = require("powershell")
languages["Properties file"] = require("props")
languages["PureBasic"] = require("purebasic")
languages["Python"] = require("python")
languages["R"] = require("r")
languages["REBOL"] = require("rebol")
languages["registry"] = require("registry")
languages["RC"] = require("rc")
languages["Ruby"] = require("ruby")
languages["Rust"] = require("rust")
languages["Scheme"] = require("scheme")
languages["Smalltalk"] = require("smalltalk")
languages["spice"] = require("spice")
languages["SQL"] = require("sql")
languages["S-Record"] = require("srec")
languages["Swift"] = require("swift")
languages["TCL"] = require("tcl")
languages["Tektronix extended HEX"] = require("tehex")
languages["TeX"] = require("tex")
languages["Text"] = require("text")
languages["VB / VBS"] = require("vb")
languages["txt2tags"] = require("txt2tags")
languages["Verilog"] = require("verilog")
languages["VHDL"] = require("vhdl")
languages["Visual Prolog"] = require("visualprolog")
languages["XML"] = require("xml")
languages["YAML"] = require("yaml")
languages["Abaqus"] = require("abaqus")
