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
#line 48 "ploggrammar.yy" // lalr1.cc:404


#include "plog/plogparser.h"
#include "plog/programbuilder.h"
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

#include "plog/ploggrammar.tab.hh"

// User implementation prologue.

#line 87 "ploggrammar.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 83 "ploggrammar.yy" // lalr1.cc:413


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
  case 8:
#line 193 "ploggrammar.yy" // lalr1.cc:859
    { BUILDER.define(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.term), true, LOGGER);}
#line 663 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 291 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 669 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 292 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 675 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 293 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 681 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 294 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 687 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 295 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 693 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 299 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 699 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 300 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 705 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 304 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 711 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 305 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 717 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 306 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 723 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 307 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 729 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 321 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = (yystack_[0].value.term); }
#line 735 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 322 "ploggrammar.yy" // lalr1.cc:859
    {  (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec));}
#line 741 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 326 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 747 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 327 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 753 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 328 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 759 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 329 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 765 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 330 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 771 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 331 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 777 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 332 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term)); }
#line 783 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 333 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 789 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 334 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str)))); }
#line 795 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 335 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 801 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 336 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term);}
#line 807 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 342 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec(BUILDER.termvec(), (yystack_[0].value.term));}
#line 813 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 343 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec((yystack_[2].value.termvec), (yystack_[0].value.term)); }
#line 819 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 350 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 825 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 351 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 831 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 352 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 837 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 353 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 843 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 354 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 849 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 355 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 855 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 356 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term));  }
#line 861 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 357 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec)); }
#line 867 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 358 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 873 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 359 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str))));}
#line 879 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 360 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 885 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 361 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[0].value.str)));  }
#line 891 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 362 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term); }
#line 897 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 369 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 903 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 370 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 909 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 378 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 915 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 379 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 921 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 380 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 927 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 381 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 933 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 382 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 939 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 383 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 945 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 386 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 951 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 387 "ploggrammar.yy" // lalr1.cc:859
    {  }
#line 957 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 388 "ploggrammar.yy" // lalr1.cc:859
    { }
#line 963 "ploggrammar.tab.cc" // lalr1.cc:859
    break;


#line 967 "ploggrammar.tab.cc" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -90;

  const signed char parser::yytable_ninf_ = -100;

  const short int
  parser::yypact_[] =
  {
      15,    17,    41,   -90,   -90,   -90,     8,   -90,   -90,    42,
      50,    79,    34,   110,    50,   -90,    66,   151,   -90,   107,
     -90,   184,    66,   185,   205,   -90,   176,   169,   226,   226,
     226,   -90,   179,   191,   155,   -90,    62,   170,   190,   204,
     150,   -90,   111,   -90,   -90,   212,   212,   212,   -90,   188,
     -90,     3,   201,   -90,   184,   176,   176,   206,   138,   -90,
     210,   -90,   -90,   -90,   108,   218,    -3,   -90,    51,   106,
     -90,   184,   -90,   226,   226,   226,   226,   226,   226,   -90,
     205,    71,   -90,   -90,   202,   192,   170,   212,   212,   -90,
      69,   219,   132,   141,   -90,   212,   212,   -90,   -90,   -90,
     -90,   -90,   212,   -90,   212,   212,   212,   212,   212,   -90,
     -90,   142,     5,     1,    92,   176,   176,   -90,   176,   176,
     -90,   226,   -90,   231,   243,   -90,   -90,    43,   248,   227,
     227,   227,   227,   248,   -90,   198,   -90,   249,   145,   239,
     157,   157,    44,   -90,   196,   212,   -90,   -90,    78,   250,
     235,   235,   235,   235,   250,   157,   184,   -90,   -90,   -90,
     164,    85,   -90,   242,   -90,   242,   155,   -90,   256,   -90,
     -90,   232,   255,   240,   198,   212,   273,   -90,   113,     6,
     -90,   241,   176,   275,   -90,   251,   -90,   247,   253,   122,
     157,   212,   -90,   257,   -90,    84,   254,   280,   -90,   282,
     157,   -90,    84,   246,   173,   -90,   252,   232,   144,   258,
      84,    84,   271,   -90,   -90,   -90,   -90,   289,   259,   262,
     267,   264,   -90
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     1,    11,    39,     0,     5,     7,     0,
       0,     9,    37,     0,     0,    46,     0,     0,    10,     0,
      38,     0,     0,    44,     0,     3,     0,     0,     0,     0,
       0,    73,    72,     0,    62,     2,     0,     0,     0,     0,
      54,    45,     0,    52,    53,     0,     0,     0,    87,    86,
      88,     0,     0,    16,     0,     0,     0,    72,     0,    13,
      14,    24,    15,    17,     0,    42,     0,    72,     0,     0,
      70,     0,     8,     0,     0,     0,     0,     0,     0,    51,
       0,     0,   101,    61,     0,     0,     0,     0,     0,    47,
       0,    86,     0,     0,    83,     0,     0,    96,    94,    92,
      95,    93,     0,    97,     0,     0,     0,     0,     0,   106,
      75,     0,     0,     0,     0,     0,     0,    12,     0,     0,
      23,     0,    41,     0,     0,    71,    74,     0,    64,    66,
      68,    69,    67,    65,   102,     0,    50,     0,     0,     0,
      57,    90,     0,    48,     0,     0,    85,    89,     0,    77,
      79,    81,    82,    80,    78,   100,     0,    36,    25,    21,
      34,     0,    33,    18,    19,    20,    22,    43,     0,    63,
      60,     0,     0,     0,     0,     0,    55,    49,     0,    84,
      76,     0,     0,    26,    40,     0,   104,     0,     0,     0,
      91,     0,    84,     0,    32,     0,     0,     0,    58,     0,
      56,    35,     0,     0,    27,   105,     0,     0,     0,     0,
       0,     0,     0,   103,    31,    28,    30,    29,     0,     0,
       0,     0,    59
  };

  const short int
  parser::yypgoto_[] =
  {
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -22,   -90,
     -90,   244,   -90,    48,   -90,   119,   -90,   293,   -90,   -90,
     -90,   291,   -90,   -90,   -90,   -13,   -90,   -85,   -18,    -7,
     236,   -45,   -89,   100,   -15,   171,   101,   287
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,     8,     9,    11,    18,   160,    59,
      60,    61,    62,   204,   161,   162,    63,    10,    12,    20,
      66,    16,    23,    41,    42,    43,    44,    81,   110,    64,
     111,    51,   142,   108,    82,    83,   186,    25
  };

  const short int
  parser::yytable_[] =
  {
      92,    93,    94,    33,    58,   144,   148,   123,   116,    52,
      96,    97,   116,   124,    34,    -4,   -99,     3,    98,   -99,
      99,    68,    69,    70,    84,   100,   118,   101,   102,   103,
     118,   104,   105,   112,   113,   159,   158,   119,   106,   107,
     -99,   119,   140,   141,     4,     5,     5,    34,    13,   114,
     141,   149,     6,   156,   175,    15,   178,   150,    73,   151,
     152,   153,   154,   155,    34,   134,   128,   129,   130,   131,
     132,   133,   125,   139,    19,    79,    74,   169,   176,    75,
      76,   135,   143,    45,   136,    46,    77,    78,   175,   189,
      45,    17,    46,    24,   163,   182,   164,   165,    47,    73,
     141,    48,    49,    50,    80,    47,   121,   202,    48,    49,
      50,    80,   179,    73,   166,    73,    27,    74,    21,   183,
      75,    76,   121,   175,    89,   203,   126,    77,    78,    90,
     190,    74,   135,    74,    75,    76,    75,    76,   180,    96,
     126,    77,    78,    77,    78,   116,   200,   192,    96,    34,
     210,   117,   156,   146,   172,   173,   199,   102,    87,    26,
     104,   105,    73,   118,    96,   211,   102,   106,   107,   104,
     105,   116,   157,    88,   119,   147,   106,   107,   214,   210,
      74,    65,   102,    75,    76,   104,   105,   181,    53,   118,
      77,    78,   106,   107,   211,    54,    55,    28,   -98,    56,
     119,   -98,    71,    36,    72,    28,   135,    29,    37,   177,
      40,    95,    30,    85,   109,    31,    57,    38,    39,    45,
      30,    46,   -98,    31,    32,    40,    45,    86,    46,   115,
      55,   122,   138,    45,    47,    46,   137,    48,    49,    50,
      80,    47,   145,   167,    48,    49,    50,    28,    47,    29,
     208,    48,    91,    50,    97,   168,    76,   171,   216,   217,
     174,    98,    30,    99,   105,    31,    67,   118,   100,   184,
     101,   185,   103,    74,   187,   102,    75,    76,   104,   105,
     188,   191,   193,    77,   195,   106,   196,   198,   197,   206,
     207,   201,   212,   205,   218,   210,   220,   221,   222,   215,
     219,   194,    14,   209,   120,    22,   170,   127,   213,    35
  };

  const unsigned char
  parser::yycheck_[] =
  {
      45,    46,    47,    21,    26,    90,    95,    10,     7,    24,
       7,     8,     7,    16,    21,     0,    10,     0,    15,    13,
      17,    28,    29,    30,    37,    22,    25,    24,    25,    26,
      25,    28,    29,    55,    56,    34,    31,    36,    35,    36,
      34,    36,    87,    88,     3,     4,     4,    54,    40,    56,
      95,    96,    11,    10,    10,     5,   145,   102,     7,   104,
     105,   106,   107,   108,    71,    80,    73,    74,    75,    76,
      77,    78,    21,    86,    40,    13,    25,    34,    34,    28,
      29,    10,    13,    21,    13,    23,    35,    36,    10,   174,
      21,    12,    23,    27,   116,    10,   118,   119,    36,     7,
     145,    39,    40,    41,    42,    36,    14,    23,    39,    40,
      41,    42,    34,     7,   121,     7,     9,    25,     8,    34,
      28,    29,    14,    10,    13,    41,    34,    35,    36,    18,
     175,    25,    10,    25,    28,    29,    28,    29,   156,     7,
      34,    35,    36,    35,    36,     7,   191,    34,     7,   156,
       6,    13,    10,    21,     9,    10,    34,    25,     8,     8,
      28,    29,     7,    25,     7,    21,    25,    35,    36,    28,
      29,     7,    30,    23,    36,    34,    35,    36,    34,     6,
      25,    12,    25,    28,    29,    28,    29,    23,    12,    25,
      35,    36,    35,    36,    21,    19,    20,    21,    10,    23,
      36,    13,    23,    18,    13,    21,    10,    23,    23,    13,
      40,    23,    36,    23,    13,    39,    40,    32,    33,    21,
      36,    23,    34,    39,    40,    40,    21,    23,    23,    23,
      20,    13,    40,    21,    36,    23,    34,    39,    40,    41,
      42,    36,    23,    12,    39,    40,    41,    21,    36,    23,
     202,    39,    40,    41,     8,    12,    29,     8,   210,   211,
      21,    15,    36,    17,    29,    39,    40,    25,    22,    13,
      24,    39,    26,    25,    19,    25,    28,    29,    28,    29,
      40,     8,    41,    35,     9,    35,    35,    34,    41,     9,
       8,    34,    40,    39,    23,     6,    34,    30,    34,    41,
      41,   182,     9,   203,    60,    14,   135,    71,   207,    22
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    44,    45,     0,     3,     4,    11,    46,    47,    48,
      60,    49,    61,    40,    60,     5,    64,    12,    50,    40,
      62,     8,    64,    65,    27,    80,     8,     9,    21,    23,
      36,    39,    40,    71,    72,    80,    18,    23,    32,    33,
      40,    66,    67,    68,    69,    21,    23,    36,    39,    40,
      41,    74,    77,    12,    19,    20,    23,    40,    51,    52,
      53,    54,    55,    59,    72,    12,    63,    40,    72,    72,
      72,    23,    13,     7,    25,    28,    29,    35,    36,    13,
      42,    70,    77,    78,    68,    23,    23,     8,    23,    13,
      18,    40,    74,    74,    74,    23,     7,     8,    15,    17,
      22,    24,    25,    26,    28,    29,    35,    36,    76,    13,
      71,    73,    51,    51,    72,    23,     7,    13,    25,    36,
      54,    14,    13,    10,    16,    21,    34,    73,    72,    72,
      72,    72,    72,    72,    77,    10,    13,    34,    40,    68,
      74,    74,    75,    13,    70,    23,    21,    34,    75,    74,
      74,    74,    74,    74,    74,    74,    10,    30,    31,    34,
      51,    57,    58,    51,    51,    51,    72,    12,    12,    34,
      78,     8,     9,    10,    21,    10,    34,    13,    75,    34,
      71,    23,    10,    34,    13,    39,    79,    19,    40,    70,
      74,     8,    34,    41,    58,     9,    35,    41,    34,    34,
      74,    34,    23,    41,    56,    39,     9,     8,    56,    76,
       6,    21,    40,    79,    34,    41,    56,    56,    23,    41,
      34,    30,    34
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    43,    44,    44,    44,    45,    45,    46,    47,    48,
      49,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    53,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    60,    61,    61,
      62,    62,    63,    63,    64,    65,    65,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    66,    66,    79,    80
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     5,     4,     0,     2,     0,     1,     5,     2,
       2,     0,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     3,     4,     6,     3,     3,
       3,     3,     3,     1,     1,     4,     3,     2,     2,     0,
       6,     4,     1,     3,     2,     2,     0,     2,     3,     4,
       3,     2,     1,     1,     1,     4,     6,     3,     6,    13,
       3,     1,     1,     4,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     4,     3,     1,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     1,     2,     8,     5,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"<EOF>\"", "error", "$undefined", "SORTDEFKEYWORD", "ATTDEFKEYWORD",
  "STMTDEFKEYWORD", "\"&\"", "\"+\"", "\"=\"", "\":\"", "\",\"",
  "\"#const\"", "SORT_NAME", "\".\"", "\"..\"", "\">=\"", "\"->\"",
  "\">\"", "\":-\"", "\"{\"", "\"[\"", "\"|\"", "\"<=\"", "\"(\"", "\"<\"",
  "\"*\"", "\"!=\"", "\"?\"", "\"\\\\\"", "\"^\"", "\"}\"", "\"]\"",
  "\"random\"", "\"pr\"", "\")\"", "\"/\"", "\"-\"", "UBNOT", "UMINUS",
  "\"<NUMBER>\"", "\"<IDENTIFIER>\"", "\"<VARIABLE>\"", "\"not\"",
  "$accept", "program", "directives", "directive", "const_decl",
  "sorts_sec", "sort_defs", "sort_def", "sort_expr", "range",
  "concatenation", "concat_elem", "functional_symbol", "cond",
  "sort_expr_list", "var_sort_expr", "curly_brackets", "atts_sec",
  "att_defs", "att_def", "sort_name_list", "stmts_sec", "stmts", "stmt",
  "head", "head_atom", "random_atom", "body", "constterm",
  "comparable_constterm", "consttermvec", "term", "ntermvec", "cmp",
  "literal", "e_literal", "probability", "query", YY_NULLPTR
  };

#if PLOGGRAMMAR_DEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,   174,   174,   175,   175,   185,   186,   189,   193,   202,
     205,   206,   209,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   224,   227,   228,   231,   234,   235,   238,   239,
     240,   241,   247,   248,   251,   252,   255,   262,   264,   265,
     268,   269,   272,   273,   280,   283,   284,   291,   292,   293,
     294,   295,   299,   300,   304,   305,   306,   307,   310,   311,
     315,   316,   321,   322,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   342,   343,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     369,   370,   378,   379,   380,   381,   382,   383,   386,   387,
     388,   391,   392,   396,   397,   400,   403
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
      35,    36,    37,    38,    39,    40,    41,    42
    };
    const unsigned int user_token_number_max_ = 297;
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
#line 1555 "ploggrammar.tab.cc" // lalr1.cc:1167
