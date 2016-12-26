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


#include "plog/plogparser.h"
#include "plog/programbuilder.h"
#include <gringo/base.hh>
#include <climits>
using Relation = Gringo::Relation;
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


#line 74 "ploggrammar.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "plog/ploggrammar.tab.hh"

// User implementation prologue.

#line 88 "ploggrammar.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 83 "ploggrammar.yy" // lalr1.cc:413


void PlogGrammar::parser::error(DefaultLocation const &l, std::string const &msg) {
    lexer->parseError(l, msg);
}


#line 98 "ploggrammar.tab.cc" // lalr1.cc:413


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
#line 184 "ploggrammar.tab.cc" // lalr1.cc:479

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
#line 210 "ploggrammar.yy" // lalr1.cc:859
    { BUILDER.define(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.term), true, LOGGER);}
#line 664 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 226 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.sortdef(yylhs.location, String::fromRep((yystack_[3].value.str)),(yystack_[1].value.sortexpr));}
#line 670 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 231 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,(yystack_[0].value.sortexprvec)); }
#line 676 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 233 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,String::fromRep((yystack_[0].value.str)));}
#line 682 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 235 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::UNION,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 688 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 236 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::INTERSECT,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 694 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 237 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::SUBTRACT,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 700 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 238 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = (yystack_[1].value.sortexpr);}
#line 706 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 241 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 712 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 244 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexprvec) = BUILDER.sortexprvec( (yystack_[1].value.sortexprvec),(yystack_[0].value.sortexpr));}
#line 718 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 245 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexprvec) = BUILDER.sortexprvec(BUILDER.sortexprvec(), (yystack_[0].value.sortexpr));}
#line 724 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 248 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = (yystack_[1].value.sortexpr);}
#line 730 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 252 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location, Symbol::createId(String::fromRep((yystack_[3].value.str))), (yystack_[1].value.varsortexprvec));}
#line 736 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 254 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location, Symbol::createId(String::fromRep((yystack_[5].value.str))), (yystack_[3].value.varsortexprvec), (yystack_[0].value.cond));}
#line 742 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 257 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.cond) = BUILDER.cond((yystack_[1].value.rel), String::fromRep((yystack_[2].value.str)),String::fromRep((yystack_[0].value.str)));}
#line 748 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 258 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.cond) = BUILDER.cond( LogicBinOp::OR, (yystack_[2].value.cond),(yystack_[0].value.cond)); }
#line 754 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 259 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.cond) = BUILDER.cond( LogicBinOp::AND, (yystack_[2].value.cond),(yystack_[0].value.cond)); }
#line 760 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 260 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.cond) = (yystack_[1].value.cond);}
#line 766 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 266 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexprvec) = BUILDER.varsortexprvec((yystack_[2].value.varsortexprvec),(yystack_[0].value.varsortexpr)); }
#line 772 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 267 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexprvec) = BUILDER.varsortexprvec(BUILDER.varsortexprvec(),(yystack_[0].value.varsortexpr)); }
#line 778 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 270 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexpr) = BUILDER.varsortexpr((yystack_[0].value.sortexpr), nullptr);}
#line 784 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 271 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexpr) = BUILDER.varsortexpr((yystack_[3].value.sortexpr), String::fromRep((yystack_[1].value.str)));}
#line 790 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 274 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, (yystack_[1].value.termvec));}
#line 796 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 275 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, BUILDER.termvec());}
#line 802 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 288 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.attdecl(yylhs.location, String::fromRep((yystack_[5].value.str)),(yystack_[3].value.sortexprvec),(yystack_[1].value.sortexpr));}
#line 808 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 289 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.attdecl(yylhs.location, String::fromRep((yystack_[3].value.str)), BUILDER.sortexprvec(), (yystack_[1].value.sortexpr));}
#line 814 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 292 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexprvec)= BUILDER.sortexprvec(BUILDER.sortexprvec(), (yystack_[0].value.sortexpr));}
#line 820 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 294 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexprvec)= BUILDER.sortexprvec((yystack_[2].value.sortexprvec),(yystack_[0].value.sortexpr));}
#line 826 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 312 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[1].value.lit)); }
#line 832 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 313 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[2].value.lit)); }
#line 838 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 314 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[3].value.lit), (yystack_[1].value.body)); }
#line 844 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 315 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, BUILDER.lit(false), (yystack_[1].value.body)); }
#line 850 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 316 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, BUILDER.lit(false)); }
#line 856 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 325 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.lit(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str)))); }
#line 862 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 326 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec));  }
#line 868 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 327 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[5].value.str)), (yystack_[3].value.termvec), (yystack_[0].value.term)); }
#line 874 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 328 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, Symbol::createId(String::fromRep((yystack_[2].value.str))), (yystack_[0].value.term)); }
#line 880 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 332 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.body) = BUILDER.body((yystack_[2].value.body), (yystack_[0].value.lit));}
#line 886 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 333 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.body) = BUILDER.body(BUILDER.body(), (yystack_[0].value.lit));}
#line 892 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 338 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = (yystack_[0].value.term); }
#line 898 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 339 "ploggrammar.yy" // lalr1.cc:859
    {  (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec));}
#line 904 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 343 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 910 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 344 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 916 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 345 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 922 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 346 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 928 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 347 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 934 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 348 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 940 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 349 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term)); }
#line 946 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 350 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 952 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 351 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str)))); }
#line 958 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 352 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 964 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 353 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term);}
#line 970 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 359 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec(BUILDER.termvec(), (yystack_[0].value.term));}
#line 976 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 360 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec((yystack_[2].value.termvec), (yystack_[0].value.term)); }
#line 982 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 367 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 988 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 368 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 994 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 369 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1000 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 370 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1006 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 371 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1012 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 372 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 1018 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 373 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term));  }
#line 1024 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 374 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec)); }
#line 1030 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 375 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 1036 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 376 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str))));}
#line 1042 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 377 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 1048 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 378 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[0].value.str)));  }
#line 1054 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 379 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term); }
#line 1060 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 386 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec(BUILDER.termvec(), (yystack_[0].value.term)); }
#line 1066 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 387 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec((yystack_[2].value.termvec), (yystack_[0].value.term)); }
#line 1072 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 395 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::GT;  }
#line 1078 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 396 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::LT;  }
#line 1084 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 397 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::GEQ; }
#line 1090 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 398 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::LEQ; }
#line 1096 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 399 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::EQ;  }
#line 1102 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 400 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::NEQ; }
#line 1108 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 403 "ploggrammar.yy" // lalr1.cc:859
    {  (yylhs.value.lit) = BUILDER.lit(yylhs.location,(yystack_[0].value.term)); }
#line 1114 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 404 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location,(yystack_[2].value.term), (yystack_[1].value.rel), (yystack_[0].value.term)); }
#line 1120 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 407 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.elit(yylhs.location,  (yystack_[0].value.lit), false);}
#line 1126 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 408 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.elit(yylhs.location,  (yystack_[0].value.lit), true); }
#line 1132 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 412 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.pratom(yylhs.location,(yystack_[6].value.lit),(yystack_[4].value.body),(yystack_[1].value.prob));}
#line 1138 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 413 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.pratom(yylhs.location,(yystack_[4].value.lit),BUILDER.body(),(yystack_[1].value.prob));}
#line 1144 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 416 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.prob) = BUILDER.prob(yylhs.location,(yystack_[2].value.num),(yystack_[0].value.num));}
#line 1150 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 419 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.query(yylhs.location, (yystack_[1].value.lit));}
#line 1156 "ploggrammar.tab.cc" // lalr1.cc:859
    break;


#line 1160 "ploggrammar.tab.cc" // lalr1.cc:859
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


  const short int parser::yypact_ninf_ = -179;

  const signed char parser::yytable_ninf_ = -5;

  const short int
  parser::yypact_[] =
  {
      11,    15,   164,  -179,  -179,  -179,   -19,  -179,  -179,    22,
      41,     9,    72,    69,    41,  -179,    96,    98,  -179,   146,
    -179,   231,    96,   190,   210,  -179,   197,   197,   236,   236,
     236,  -179,   140,   154,    80,  -179,    -2,   160,    68,  -179,
     128,  -179,   210,   210,   210,  -179,   166,  -179,   104,   181,
     223,   197,   197,   175,  -179,    81,  -179,   184,  -179,  -179,
    -179,     0,   112,   132,  -179,   137,   145,  -179,   231,  -179,
     236,   236,   236,   236,   236,   236,  -179,   210,    32,  -179,
    -179,   148,   210,   210,  -179,    61,   156,   167,  -179,   210,
     210,  -179,  -179,  -179,  -179,  -179,   210,  -179,   210,   210,
     210,   210,   210,  -179,  -179,  -179,     2,    45,    46,   126,
     197,   197,  -179,   197,   197,  -179,   236,  -179,   197,   197,
    -179,  -179,    39,   239,   182,   182,   182,   182,   239,  -179,
     202,  -179,    54,   178,   178,    84,  -179,   139,  -179,  -179,
     111,   254,   185,   185,   185,   185,   254,   178,   231,  -179,
    -179,  -179,   174,   116,  -179,   194,  -179,   194,    80,    48,
     180,  -179,  -179,   202,   201,   210,   212,  -179,  -179,  -179,
     186,   197,   214,  -179,   124,   189,   178,   210,   195,  -179,
      63,   221,   200,   225,   178,  -179,    63,   263,    97,   189,
     209,  -179,    19,   211,    63,    63,   242,  -179,  -179,  -179,
    -179,   249,  -179
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     1,    11,    40,     0,     5,     7,     0,
       0,     9,    38,     0,     0,    47,     0,     0,    10,     0,
      39,     0,     0,    45,     0,     3,     0,     0,     0,     0,
       0,    71,    70,     0,    60,     2,     0,     0,    54,    46,
       0,    53,     0,     0,     0,    85,    84,    86,    96,     0,
       0,     0,     0,    70,    16,     0,    13,    14,    24,    15,
      17,     0,    43,     0,    70,     0,     0,    68,     0,     8,
       0,     0,     0,     0,     0,     0,    52,     0,     0,    98,
      59,     0,     0,     0,    48,     0,     0,     0,    81,     0,
       0,    94,    92,    90,    93,    91,     0,    95,     0,     0,
       0,     0,     0,   103,    37,    73,     0,     0,     0,     0,
       0,     0,    12,     0,     0,    23,     0,    42,     0,     0,
      69,    72,     0,    62,    64,    66,    67,    65,    63,    99,
       0,    51,     0,    57,    88,     0,    49,     0,    83,    87,
       0,    75,    77,    79,    80,    78,    76,    97,     0,    36,
      25,    21,    34,     0,    33,    18,    19,    20,    22,    44,
       0,    61,    58,     0,     0,     0,    55,    50,    82,    74,
       0,     0,    26,    41,     0,     0,    89,     0,     0,    32,
       0,     0,     0,     0,    56,    35,     0,     0,    27,     0,
       0,   101,     0,     0,     0,     0,     0,   102,    31,    28,
      30,    29,   100
  };

  const short int
  parser::yypgoto_[] =
  {
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,   -22,  -179,
    -179,   205,  -179,  -178,  -179,    88,  -179,   255,  -179,  -179,
    -179,   261,  -179,  -179,  -179,   199,   -79,   -18,    -7,   208,
     -42,   196,   102,   -15,   153,   101,   269
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,     8,     9,    11,    18,   152,    56,
      57,    58,    59,   188,   153,   154,    60,    10,    12,    20,
      63,    16,    23,    39,    40,    41,    78,   105,    61,   106,
      48,   135,   102,    79,    80,   183,    25
  };

  const short int
  parser::yytable_[] =
  {
      86,    87,    88,    33,    55,    62,   137,    70,   192,    49,
      76,    -4,   148,   116,    34,     3,   200,   201,    42,    13,
      43,    65,    66,    67,    71,   194,     5,    72,    73,   107,
     108,   149,    44,    74,    75,    45,    46,    47,    77,   195,
     133,   134,   130,    34,   131,   109,    15,   134,   141,   148,
      17,   198,   111,   111,   142,   111,   143,   144,   145,   146,
     147,    34,   129,   123,   124,   125,   126,   127,   128,   113,
     113,   161,   113,   136,   163,   150,    82,    21,   151,   114,
     114,    42,   114,    43,   174,   186,   164,    70,   111,   155,
      83,   156,   157,   112,   165,    44,   159,   160,    45,    46,
      47,    77,   187,   194,    71,   113,    26,    72,    73,   158,
      19,    90,    91,    74,    75,   114,   166,   195,    92,   111,
      93,   165,    24,   176,   117,    94,   171,    95,    96,    97,
     169,    98,    99,    70,   130,   184,   113,   100,   101,   116,
      84,    34,   118,   168,    70,    85,   114,   119,   172,   130,
      71,   167,    70,    72,    73,    27,   181,   120,   121,    74,
      75,    71,    68,    90,    72,    73,    69,     4,     5,    71,
      74,    75,    72,    73,    90,     6,   138,   121,    74,    75,
      96,   111,    81,    98,    99,    90,    38,   111,    89,   100,
     101,    96,   173,   103,    98,    99,   170,   110,   113,   139,
     100,   101,    96,    51,   113,    98,    99,    36,   114,   175,
      73,   100,   101,    99,   114,    50,    51,    28,   113,    52,
     177,    37,    42,   180,    43,   178,   182,   185,    38,   189,
      42,    30,    43,   190,    31,    53,    44,   191,    54,    45,
      46,    47,    77,    28,    44,    29,   197,    45,    46,    47,
     199,    28,   104,    29,   202,   194,    28,    30,    29,   179,
      31,    32,   115,    71,    14,    30,    72,    73,    31,    32,
      30,    91,    74,    31,    64,    22,   122,    92,    96,    93,
     132,    98,    99,   162,    94,   140,    95,   100,    97,   193,
     196,    35
  };

  const unsigned char
  parser::yycheck_[] =
  {
      42,    43,    44,    21,    26,    27,    85,     7,   186,    24,
      12,     0,    10,    13,    21,     0,   194,   195,    20,    38,
      22,    28,    29,    30,    24,     6,     4,    27,    28,    51,
      52,    29,    34,    33,    34,    37,    38,    39,    40,    20,
      82,    83,    10,    50,    12,    52,     5,    89,    90,    10,
      41,    32,     7,     7,    96,     7,    98,    99,   100,   101,
     102,    68,    77,    70,    71,    72,    73,    74,    75,    24,
      24,    32,    24,    12,    20,    30,     8,     8,    32,    34,
      34,    20,    34,    22,   163,    22,    32,     7,     7,   111,
      22,   113,   114,    12,    10,    34,   118,   119,    37,    38,
      39,    40,    39,     6,    24,    24,     8,    27,    28,   116,
      38,     7,     8,    33,    34,    34,    32,    20,    14,     7,
      16,    10,    26,   165,    12,    21,    10,    23,    24,    25,
     148,    27,    28,     7,    10,   177,    24,    33,    34,    13,
      12,   148,    10,    32,     7,    17,    34,    15,    32,    10,
      24,    12,     7,    27,    28,     9,    32,    20,    32,    33,
      34,    24,    22,     7,    27,    28,    12,     3,     4,    24,
      33,    34,    27,    28,     7,    11,    20,    32,    33,    34,
      24,     7,    22,    27,    28,     7,    38,     7,    22,    33,
      34,    24,    12,    12,    27,    28,    22,    22,    24,    32,
      33,    34,    24,    19,    24,    27,    28,    17,    34,     8,
      28,    33,    34,    28,    34,    18,    19,    20,    24,    22,
       8,    31,    20,     9,    22,    39,    37,    32,    38,     8,
      20,    34,    22,    33,    37,    38,    34,    12,    41,    37,
      38,    39,    40,    20,    34,    22,    37,    37,    38,    39,
      39,    20,    29,    22,    12,     6,    20,    34,    22,   171,
      37,    38,    57,    24,     9,    34,    27,    28,    37,    38,
      34,     8,    33,    37,    38,    14,    68,    14,    24,    16,
      81,    27,    28,   130,    21,    89,    23,    33,    25,   187,
     189,    22
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    43,    44,     0,     3,     4,    11,    45,    46,    47,
      59,    48,    60,    38,    59,     5,    63,    41,    49,    38,
      61,     8,    63,    64,    26,    78,     8,     9,    20,    22,
      34,    37,    38,    69,    70,    78,    17,    31,    38,    65,
      66,    67,    20,    22,    34,    37,    38,    39,    72,    75,
      18,    19,    22,    38,    41,    50,    51,    52,    53,    54,
      58,    70,    50,    62,    38,    70,    70,    70,    22,    12,
       7,    24,    27,    28,    33,    34,    12,    40,    68,    75,
      76,    22,     8,    22,    12,    17,    72,    72,    72,    22,
       7,     8,    14,    16,    21,    23,    24,    25,    27,    28,
      33,    34,    74,    12,    29,    69,    71,    50,    50,    70,
      22,     7,    12,    24,    34,    53,    13,    12,    10,    15,
      20,    32,    71,    70,    70,    70,    70,    70,    70,    75,
      10,    12,    67,    72,    72,    73,    12,    68,    20,    32,
      73,    72,    72,    72,    72,    72,    72,    72,    10,    29,
      30,    32,    50,    56,    57,    50,    50,    50,    70,    50,
      50,    32,    76,    20,    32,    10,    32,    12,    32,    69,
      22,    10,    32,    12,    68,     8,    72,     8,    39,    57,
       9,    32,    37,    77,    72,    32,    22,    39,    55,     8,
      33,    12,    55,    74,     6,    20,    77,    37,    32,    39,
      55,    55,    12
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    42,    43,    43,    43,    44,    44,    45,    46,    47,
      48,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    60,
      60,    61,    61,    62,    62,    63,    64,    64,    65,    65,
      65,    65,    65,    66,    67,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    74,    75,    75,    76,    76,
      65,    65,    77,    78
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     5,     4,     0,     2,     0,     1,     5,     2,
       2,     0,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     3,     4,     6,     3,     3,
       3,     3,     3,     1,     1,     4,     3,     2,     2,     2,
       0,     6,     4,     1,     3,     2,     2,     0,     2,     3,
       4,     3,     2,     1,     1,     4,     6,     3,     3,     1,
       1,     4,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     4,     3,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       9,     7,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"<EOF>\"", "error", "$undefined", "SORTDEFKEYWORD", "ATTDEFKEYWORD",
  "STMTDEFKEYWORD", "\"&\"", "\"+\"", "\"=\"", "\":\"", "\",\"",
  "\"#const\"", "\".\"", "\"..\"", "\">=\"", "\"->\"", "\">\"", "\":-\"",
  "\"{\"", "\"[\"", "\"|\"", "\"<=\"", "\"(\"", "\"<\"", "\"*\"", "\"!=\"",
  "\"?\"", "\"\\\\\"", "\"^\"", "\"}\"", "\"]\"", "\"pr\"", "\")\"",
  "\"/\"", "\"-\"", "UBNOT", "UMINUS", "\"<NUMBER>\"", "\"<IDENTIFIER>\"",
  "\"<VARIABLE>\"", "\"not\"", "\"<SORT_NAME>\"", "$accept", "program",
  "directives", "directive", "const_decl", "sorts_sec", "sort_defs",
  "sort_def", "sort_expr", "range", "concatenation", "concat_elem",
  "functional_symbol", "cond", "var_sort_expr_list", "var_sort_expr",
  "curly_brackets", "atts_sec", "att_defs", "att_def", "sort_expr_vec",
  "stmts_sec", "stmts", "stmt", "head", "head_atom", "body", "constterm",
  "comparable_constterm", "consttermvec", "term", "ntermvec", "cmp",
  "literal", "e_literal", "probability", "query", YY_NULLPTR
  };

#if PLOGGRAMMAR_DEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,   191,   191,   192,   192,   202,   203,   206,   210,   219,
     222,   223,   226,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   241,   244,   245,   248,   251,   253,   257,   258,
     259,   260,   266,   267,   270,   271,   274,   275,   282,   284,
     285,   288,   289,   292,   293,   301,   304,   305,   312,   313,
     314,   315,   316,   320,   325,   326,   327,   328,   332,   333,
     338,   339,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   359,   360,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   386,   387,
     395,   396,   397,   398,   399,   400,   403,   404,   407,   408,
     412,   413,   416,   419
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
      35,    36,    37,    38,    39,    40,    41
    };
    const unsigned int user_token_number_max_ = 296;
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
#line 1739 "ploggrammar.tab.cc" // lalr1.cc:1167
