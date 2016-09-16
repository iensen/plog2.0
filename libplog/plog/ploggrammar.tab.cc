// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   PlogGrammar_lex

// First part of user declarations.
#line 47 "ploggrammar.yy" // lalr1.cc:404


#include "plogparser.hh"
#include "programbuilder.hh"
#include <climits>

#define BUILDER (lexer->builder())
#define LOGGER (lexer->logger())
#define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do {                                                               \
        if (N) {                                                       \
            (Current).beginFilename = YYRHSLOC (Rhs, 1).beginFilename; \
            (Current).beginLine     = YYRHSLOC (Rhs, 1).beginLine;     \
            (Current).beginColumn   = YYRHSLOC (Rhs, 1).beginColumn;   \
            (Current).endFilename   = YYRHSLOC (Rhs, N).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, N).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, N).endColumn;     \
        }                                                              \
        else {                                                         \
            (Current).beginFilename = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).beginLine     = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).beginColumn   = YYRHSLOC (Rhs, 0).endColumn;     \
            (Current).endFilename   = YYRHSLOC (Rhs, 0).endFilename;   \
            (Current).endLine       = YYRHSLOC (Rhs, 0).endLine;       \
            (Current).endColumn     = YYRHSLOC (Rhs, 0).endColumn;     \
        }                                                              \
    }                                                                  \
    while (false)

int PlogGrammar_lex(void *value, Gringo::Location* loc, PlogParser *lexer) {
    return lexer->lex(value, *loc);
}


#line 73 "ploggrammar.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ploggrammar.tab.hh"

// User implementation prologue.

#line 87 "ploggrammar.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 82 "ploggrammar.yy" // lalr1.cc:413


void PlogGrammar::parser::error(DefaultLocation const &l, std::string const &msg) {
    lexer->parseError(l, msg);
}


#line 97 "ploggrammar.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if PLOGGRAMMAR_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !PLOGGRAMMAR_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PLOGGRAMMAR_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "ploggrammar.yy" // lalr1.cc:479
namespace PlogGrammar {
#line 183 "ploggrammar.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (PlogParser *lexer_yyarg)
    :
#if PLOGGRAMMAR_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if PLOGGRAMMAR_DEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PLOGGRAMMAR_DEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PLOGGRAMMAR_DEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, lexer));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 40:
#line 271 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 663 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 272 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 669 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 273 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 675 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 274 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 681 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 275 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 687 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 279 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 693 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 280 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 699 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 284 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 705 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 285 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 711 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 286 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 717 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 287 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 723 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 301 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 729 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 302 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 735 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 303 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 741 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 304 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 747 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 305 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 753 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 306 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 759 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 307 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 765 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 308 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 771 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 309 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 777 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 310 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 783 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 311 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 789 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 317 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 795 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 318 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 801 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 322 "ploggrammar.yy" // lalr1.cc:859
    {   }
#line 807 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 323 "ploggrammar.yy" // lalr1.cc:859
    {   }
#line 813 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 329 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 819 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 330 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 825 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 331 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 831 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 332 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 837 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 333 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 843 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 334 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 849 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 335 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 855 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 336 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 861 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 337 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 867 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 338 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 873 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 339 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 879 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 346 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 885 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 347 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 891 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 351 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 897 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 352 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 903 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 358 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 909 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 359 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 915 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 360 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 921 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 361 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 927 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 362 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 933 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 363 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 939 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 366 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 945 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 367 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 951 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 368 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 957 "ploggrammar.tab.cc" // lalr1.cc:859
    break;


#line 961 "ploggrammar.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -87;

  const signed char parser::yytable_ninf_ = -93;

  const short int
  parser::yypact_[] =
  {
       6,    24,    82,   -87,   -87,   -87,   -32,   -87,   -87,    27,
      43,    86,    -2,   109,    43,   -87,    67,   124,   -87,    98,
     -87,   137,    67,   152,   165,   -87,   142,   121,   137,   137,
     -87,   111,     1,   -87,    33,   102,   126,   127,    25,   -87,
     112,   -87,   -87,   173,   173,   -87,     8,   -87,   131,   138,
     -87,   137,   142,   142,   129,    72,   -87,   151,   -87,   -87,
     -87,    76,    34,    68,    -1,   -87,   137,   137,   -87,   137,
     137,   137,   137,   137,   -87,   165,    90,   -87,   -87,   130,
     140,   102,   173,   173,   -87,    78,   164,   183,   -87,   173,
     -87,   -87,   -87,   -87,   -87,   173,   -87,   173,   173,   173,
     173,   173,   -87,    99,   178,   159,    85,   104,   142,   142,
     -87,   142,   142,   -87,   137,   179,   187,   -87,   156,   144,
     171,   171,   171,   171,   144,   -87,   155,   -87,   195,     7,
     180,    52,    52,   199,   182,   -87,   134,   173,   -87,   189,
     188,   188,   188,   188,   193,    52,   137,   -87,   -87,   -87,
      89,     0,    76,   200,   -87,   200,    99,   -87,   -87,   -87,
     -87,   184,   207,   186,   155,   173,   220,   -87,   196,   132,
      99,   142,   -87,   197,   -87,   190,   201,     9,    52,   173,
     -87,    89,   191,   225,   -87,   228,    52,   -87,   198,   184,
     214,   -87,   202,   204,   210,   208,   -87
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     1,    11,    32,     0,     5,     7,     0,
       0,     9,    30,     0,     0,    39,     0,     0,    10,     0,
      31,     0,     0,    37,     0,     3,     0,     0,     0,     0,
      65,    64,     0,     2,     0,     0,     0,     0,    47,    38,
       0,    45,    46,     0,     0,    79,    78,    80,     0,     0,
      16,    69,     0,     0,    64,     0,    13,    14,    24,    15,
      17,     0,    34,     0,     0,    61,    69,     0,     8,     0,
       0,     0,     0,     0,    44,     0,     0,    94,    54,     0,
       0,     0,     0,    84,    40,     0,    78,     0,    75,    84,
      89,    87,    85,    88,    86,     0,    90,     0,     0,     0,
       0,     0,    99,    66,    68,     0,     0,     0,    69,     0,
      12,     0,     0,    23,     0,     0,     0,    63,     0,    55,
      57,    59,    60,    58,    56,    95,     0,    43,     0,     0,
       0,    50,    81,    83,     0,    41,     0,    84,    77,     0,
      71,    73,    74,    72,    70,    93,     0,    29,    25,    21,
      28,     0,    66,    18,    19,    20,    22,    36,    33,    62,
      53,     0,     0,     0,     0,     0,    48,    42,     0,    76,
      67,     0,    26,     0,    97,     0,     0,     0,    82,     0,
      76,    27,     0,     0,    51,     0,    49,    98,     0,     0,
       0,    96,     0,     0,     0,     0,    52
  };

  const short int
  parser::yypgoto_[] =
  {
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -41,   -87,
     -87,   185,   -87,   -87,   -87,   231,   -87,   -87,   -87,   230,
     -87,   -87,   -87,   -31,   -87,   -83,    -7,   -87,   194,   -43,
     -87,   -86,   -87,   -14,   120,    58,   226
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,     8,     9,    11,    18,    55,    56,
      57,    58,    59,   151,    60,    10,    12,    20,    63,    16,
      23,    39,    40,    41,    42,    76,    61,   104,   118,    48,
     133,   134,   101,    77,    78,   174,    25
  };

  const short int
  parser::yytable_[] =
  {
      87,    88,   136,   139,    79,    67,    -4,    67,    13,   171,
      49,   106,   107,    68,    32,   162,   163,   -91,   126,   117,
     -91,    64,    65,    69,     3,    69,    70,    71,    70,    71,
      89,     5,    82,   172,    72,    73,    72,    73,    19,   131,
     132,   -91,   185,   -35,   103,    74,   132,    83,    15,   -35,
     130,   168,   140,    43,   141,   142,   143,   144,   145,   103,
     119,   125,   120,   121,   122,   123,   124,   150,   153,    44,
     154,   155,    45,    46,    47,    75,    95,   115,   109,    97,
      98,   177,    67,   116,   110,     4,     5,    99,   100,   114,
     135,   109,     6,    24,   132,   109,   111,    17,    43,   126,
      69,   152,   127,    70,    71,    67,    27,   156,   112,   111,
     109,    72,    73,   111,    44,   148,    21,    45,    46,    47,
      75,   112,   178,    69,    84,   112,    70,    71,   111,    85,
     181,    26,    62,    66,    72,    73,   186,   149,    90,   170,
     112,   -92,    38,   126,   -92,    91,   167,    92,    80,    81,
     102,   108,    93,    50,    94,    95,    96,    28,    97,    98,
      51,    52,    28,   128,    53,   -92,    99,   100,    69,    34,
      52,    70,    71,    29,    35,    43,    30,    31,    29,    72,
     129,    30,    54,    36,    37,    43,   137,   146,   147,   159,
     157,    44,    38,    43,    45,    46,    47,    75,   158,    71,
     164,    44,   161,   138,    45,    46,    47,    95,   165,    44,
      97,    98,    45,    86,    47,   166,    98,    95,    99,   100,
      97,    98,   169,   173,   111,   175,   176,   179,    99,   180,
     187,   183,   182,   188,   184,   189,   192,   194,   190,   195,
      14,   196,   113,   193,    22,   105,   160,   191,    33
  };

  const unsigned char
  parser::yycheck_[] =
  {
      43,    44,    85,    89,    35,     6,     0,     6,    40,     9,
      24,    52,    53,    12,    21,     8,     9,     9,     9,    20,
      12,    28,    29,    24,     0,    24,    27,    28,    27,    28,
      22,     4,     7,    33,    35,    36,    35,    36,    40,    82,
      83,    33,    33,     9,    51,    12,    89,    22,     5,    15,
      81,   137,    95,    20,    97,    98,    99,   100,   101,    66,
      67,    75,    69,    70,    71,    72,    73,   108,   109,    36,
     111,   112,    39,    40,    41,    42,    24,     9,     6,    27,
      28,   164,     6,    15,    12,     3,     4,    35,    36,    13,
      12,     6,    10,    26,   137,     6,    24,    11,    20,     9,
      24,   108,    12,    27,    28,     6,     8,   114,    36,    24,
       6,    35,    36,    24,    36,    30,     7,    39,    40,    41,
      42,    36,   165,    24,    12,    36,    27,    28,    24,    17,
     171,     7,    11,    22,    35,    36,   179,    33,     7,   146,
      36,     9,    40,     9,    12,    14,    12,    16,    22,    22,
      12,    22,    21,    11,    23,    24,    25,    20,    27,    28,
      18,    19,    20,    33,    22,    33,    35,    36,    24,    17,
      19,    27,    28,    36,    22,    20,    39,    40,    36,    35,
      40,    39,    40,    31,    32,    20,    22,     9,    29,    33,
      11,    36,    40,    20,    39,    40,    41,    42,    11,    28,
      20,    36,     7,    20,    39,    40,    41,    24,     9,    36,
      27,    28,    39,    40,    41,    33,    28,    24,    35,    36,
      27,    28,    33,    39,    24,    18,    40,     7,    35,    33,
      39,    41,    35,     8,    33,     7,    22,    33,    40,    29,
       9,    33,    57,    41,    14,    51,   126,   189,    22
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    45,    46,     0,     3,     4,    10,    47,    48,    49,
      59,    50,    60,    40,    59,     5,    63,    11,    51,    40,
      61,     7,    63,    64,    26,    80,     7,     8,    20,    36,
      39,    40,    70,    80,    17,    22,    31,    32,    40,    65,
      66,    67,    68,    20,    36,    39,    40,    41,    73,    77,
      11,    18,    19,    22,    40,    52,    53,    54,    55,    56,
      58,    70,    11,    62,    70,    70,    22,     6,    12,    24,
      27,    28,    35,    36,    12,    42,    69,    77,    78,    67,
      22,    22,     7,    22,    12,    17,    40,    73,    73,    22,
       7,    14,    16,    21,    23,    24,    25,    27,    28,    35,
      36,    76,    12,    70,    71,    72,    52,    52,    22,     6,
      12,    24,    36,    55,    13,     9,    15,    20,    72,    70,
      70,    70,    70,    70,    70,    77,     9,    12,    33,    40,
      67,    73,    73,    74,    75,    12,    69,    22,    20,    75,
      73,    73,    73,    73,    73,    73,     9,    29,    30,    33,
      52,    57,    70,    52,    52,    52,    70,    11,    11,    33,
      78,     7,     8,     9,    20,     9,    33,    12,    75,    33,
      70,     9,    33,    39,    79,    18,    40,    69,    73,     7,
      33,    52,    35,    41,    33,    33,    73,    39,     8,     7,
      40,    79,    22,    41,    33,    29,    33
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    44,    45,    45,    45,    46,    46,    47,    48,    49,
      50,    50,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    53,    54,    54,    55,    56,    57,    57,    58,
      59,    60,    60,    61,    61,    62,    62,    63,    64,    64,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    71,    71,    72,    72,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    74,    74,    75,    75,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    78,    78,    65,    65,    79,    80
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     5,     4,     0,     2,     0,     1,     5,     2,
       2,     0,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     3,     4,     3,     1,     3,
       2,     2,     0,     5,     3,     1,     3,     2,     2,     0,
       2,     3,     4,     3,     2,     1,     1,     1,     4,     6,
       3,     6,    13,     3,     1,     3,     3,     3,     3,     3,
       3,     2,     4,     3,     1,     1,     1,     3,     1,     0,
       3,     3,     3,     3,     3,     2,     4,     3,     1,     1,
       1,     1,     3,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     1,     2,     8,     5,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"<EOF>\"", "error", "$undefined", "SORTDEFKEYWORD", "ATTDEFKEYWORD",
  "STMTDEFKEYWORD", "\"+\"", "\"=\"", "\":\"", "\",\"", "\"#const\"",
  "SORT_NAME", "\".\"", "\"..\"", "\">=\"", "\"->\"", "\">\"", "\":-\"",
  "\"{\"", "\"[\"", "\"|\"", "\"<=\"", "\"(\"", "\"<\"", "\"*\"", "\"!=\"",
  "\"?\"", "\"\\\\\"", "\"^\"", "\"}\"", "\"]\"", "\"random\"", "\"pr\"",
  "\")\"", "\";\"", "\"/\"", "\"-\"", "UBNOT", "UMINUS", "\"<NUMBER>\"",
  "\"<IDENTIFIER>\"", "\"<VARIABLE>\"", "\"not\"", "AND", "$accept",
  "program", "directives", "directive", "const_decl", "sorts_sec",
  "sort_defs", "sort_def", "sort_expr", "range", "concatenation",
  "concat_elem", "functional_symbol", "sort_expr_list", "curly_brackets",
  "atts_sec", "att_defs", "att_def", "sort_name_list", "stmts_sec",
  "stmts", "stmt", "head", "head_atom", "random_atom", "body", "constterm",
  "consttermvec", "constargvec", "term", "ntermvec", "termvec", "cmp",
  "literal", "e_literal", "probability", "query", YY_NULLPTR
  };

#if PLOGGRAMMAR_DEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,   168,   168,   169,   169,   179,   180,   183,   187,   196,
     199,   200,   203,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   218,   221,   222,   225,   228,   231,   232,   235,
     242,   244,   245,   248,   249,   252,   253,   260,   263,   264,
     271,   272,   273,   274,   275,   279,   280,   284,   285,   286,
     287,   290,   291,   295,   296,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   317,   318,   322,   323,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   346,   347,   351,   352,   358,   359,   360,   361,   362,
     363,   366,   367,   368,   371,   372,   376,   377,   380,   383
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PLOGGRAMMAR_DEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
    };
    const unsigned int user_token_number_max_ = 298;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 19 "ploggrammar.yy" // lalr1.cc:1167
} // PlogGrammar
#line 1524 "ploggrammar.tab.cc" // lalr1.cc:1167
