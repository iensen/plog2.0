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
#line 211 "ploggrammar.yy" // lalr1.cc:859
    { BUILDER.define(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.term), true, LOGGER);}
#line 664 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 227 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.sortdef(yylhs.location, String::fromRep((yystack_[3].value.str)),(yystack_[1].value.sortexpr));}
#line 670 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 232 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,(yystack_[0].value.sortexprvec)); }
#line 676 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 234 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,Symbol::createId(String::fromRep((yystack_[0].value.str))));}
#line 682 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 236 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::UNION,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 688 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 237 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::INTERSECT,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 694 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 238 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location,SEBinOp::SUBTRACT,(yystack_[2].value.sortexpr),(yystack_[0].value.sortexpr));}
#line 700 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 239 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = (yystack_[1].value.sortexpr);}
#line 706 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 242 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 712 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 245 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexprvec) = BUILDER.sortexprvec( (yystack_[1].value.sortexprvec),(yystack_[0].value.sortexpr));}
#line 718 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 246 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.sortexprvec) = BUILDER.sortexprvec(BUILDER.sortexprvec(), (yystack_[0].value.sortexpr));}
#line 724 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 249 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = (yystack_[1].value.sortexpr);}
#line 730 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 253 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location, Symbol::createId(String::fromRep((yystack_[3].value.str))), (yystack_[1].value.varsortexprvec));}
#line 736 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 255 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr) = BUILDER.sortexpr(yylhs.location, Symbol::createId(String::fromRep((yystack_[5].value.str))), (yystack_[3].value.varsortexprvec), (yystack_[0].value.cond));}
#line 742 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 258 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.cond) = BUILDER.cond((yystack_[1].value.rel), String::fromRep((yystack_[2].value.str)),String::fromRep((yystack_[0].value.str)));}
#line 748 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 259 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.cond) = BUILDER.cond( LogicBinOp::OR, (yystack_[2].value.cond),(yystack_[0].value.cond)); }
#line 754 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 260 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.cond) = BUILDER.cond( LogicBinOp::AND, (yystack_[2].value.cond),(yystack_[0].value.cond)); }
#line 760 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 261 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.cond) = (yystack_[1].value.cond);}
#line 766 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 267 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexprvec) = BUILDER.varsortexprvec((yystack_[2].value.varsortexprvec),(yystack_[0].value.varsortexpr)); }
#line 772 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 268 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexprvec) = BUILDER.varsortexprvec(BUILDER.varsortexprvec(),(yystack_[0].value.varsortexpr)); }
#line 778 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 271 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexpr) = BUILDER.varsortexpr((yystack_[0].value.sortexpr), nullptr);}
#line 784 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 272 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.varsortexpr) = BUILDER.varsortexpr((yystack_[3].value.sortexpr), String::fromRep((yystack_[1].value.str)));}
#line 790 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 275 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, (yystack_[1].value.termvec));}
#line 796 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 276 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexpr)=BUILDER.sortexpr(yylhs.location, BUILDER.termvec());}
#line 802 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 289 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.attdecl(yylhs.location, String::fromRep((yystack_[5].value.str)),(yystack_[3].value.sortexprvec),(yystack_[1].value.sortexpr));}
#line 808 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 290 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.attdecl(yylhs.location, String::fromRep((yystack_[3].value.str)), BUILDER.sortexprvec(), (yystack_[1].value.sortexpr));}
#line 814 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 293 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexprvec)= BUILDER.sortexprvec((yylhs.value.sortexprvec)= BUILDER.sortexprvec(), (yystack_[0].value.sortexpr));}
#line 820 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 295 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.sortexprvec)= BUILDER.sortexprvec((yystack_[2].value.sortexprvec),(yystack_[0].value.sortexpr));}
#line 826 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 313 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[1].value.lit)); }
#line 832 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 314 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[2].value.lit)); }
#line 838 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 315 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, (yystack_[3].value.lit), (yystack_[1].value.body)); }
#line 844 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 316 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, BUILDER.lit(false), (yystack_[1].value.body)); }
#line 850 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 317 "ploggrammar.yy" // lalr1.cc:859
    {  BUILDER.rule(yylhs.location, BUILDER.lit(false)); }
#line 856 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 326 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[0].value.str)),BUILDER.termvec()); }
#line 862 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 327 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec));  }
#line 868 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 328 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[5].value.str)), (yystack_[3].value.termvec), (yystack_[0].value.term)); }
#line 874 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 329 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[2].value.str)), (yystack_[0].value.term)); }
#line 880 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 332 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[3].value.str)),String::fromRep((yystack_[1].value.str)));}
#line 886 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 333 "ploggrammar.yy" // lalr1.cc:859
    {
             (yylhs.value.lit) = BUILDER.lit(yylhs.location, String::fromRep((yystack_[10].value.str)),String::fromRep((yystack_[5].value.str)));}
#line 893 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 339 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.body) = BUILDER.body((yystack_[2].value.body), (yystack_[0].value.lit));}
#line 899 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 340 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.body) = BUILDER.body(BUILDER.body(), (yystack_[0].value.lit));}
#line 905 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 345 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = (yystack_[0].value.term); }
#line 911 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 346 "ploggrammar.yy" // lalr1.cc:859
    {  (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec));}
#line 917 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 350 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 923 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 351 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 929 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 352 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 935 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 353 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 941 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 354 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 947 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 355 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 953 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 356 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term)); }
#line 959 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 357 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 965 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 358 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str)))); }
#line 971 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 359 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 977 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 360 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term);}
#line 983 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 366 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec(BUILDER.termvec(), (yystack_[0].value.term));}
#line 989 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 367 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec((yystack_[2].value.termvec), (yystack_[0].value.term)); }
#line 995 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 374 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::ADD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1001 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 375 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::SUB, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1007 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 376 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MUL, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1013 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 377 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::DIV, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1019 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 378 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::MOD, (yystack_[2].value.term), (yystack_[0].value.term));  }
#line 1025 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 379 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, BinOp::POW, (yystack_[2].value.term), (yystack_[0].value.term)); }
#line 1031 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 380 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::NEG, (yystack_[0].value.term));  }
#line 1037 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 381 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[3].value.str)), (yystack_[1].value.termvec)); }
#line 1043 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 382 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, UnOp::ABS, (yystack_[1].value.term)); }
#line 1049 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 383 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createId(String::fromRep((yystack_[0].value.str))));}
#line 1055 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 384 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, Symbol::createNum((yystack_[0].value.num))); }
#line 1061 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 385 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = BUILDER.term(yylhs.location, String::fromRep((yystack_[0].value.str)));  }
#line 1067 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 386 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.term) = (yystack_[1].value.term); }
#line 1073 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 393 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec(BUILDER.termvec(), (yystack_[0].value.term)); }
#line 1079 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 394 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.termvec) = BUILDER.termvec((yystack_[2].value.termvec), (yystack_[0].value.term)); }
#line 1085 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 402 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::GT;  }
#line 1091 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 403 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::LT;  }
#line 1097 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 404 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::GEQ; }
#line 1103 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 405 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::LEQ; }
#line 1109 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 406 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::EQ;  }
#line 1115 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 407 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.rel) = Relation::NEQ; }
#line 1121 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 410 "ploggrammar.yy" // lalr1.cc:859
    {  (yylhs.value.lit) = BUILDER.lit(yylhs.location,(yystack_[0].value.term)); }
#line 1127 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 411 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.lit) = BUILDER.lit(yylhs.location,(yystack_[2].value.term), (yystack_[1].value.rel), (yystack_[0].value.term)); }
#line 1133 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 414 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.elit(yylhs.location,  (yystack_[0].value.lit), false);}
#line 1139 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 415 "ploggrammar.yy" // lalr1.cc:859
    { (yylhs.value.lit) = BUILDER.elit(yylhs.location,  (yystack_[0].value.lit), true); }
#line 1145 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 419 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.pratom(yylhs.location,(yystack_[6].value.lit),(yystack_[4].value.body),(yystack_[1].value.prob));}
#line 1151 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 420 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.pratom(yylhs.location,(yystack_[4].value.lit),BUILDER.body(),(yystack_[1].value.prob));}
#line 1157 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 423 "ploggrammar.yy" // lalr1.cc:859
    {(yylhs.value.prob) = BUILDER.prob(yylhs.location,(yystack_[2].value.num),(yystack_[0].value.num));}
#line 1163 "ploggrammar.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 426 "ploggrammar.yy" // lalr1.cc:859
    {BUILDER.query(yylhs.location, (yystack_[1].value.lit));}
#line 1169 "ploggrammar.tab.cc" // lalr1.cc:859
    break;


#line 1173 "ploggrammar.tab.cc" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -83;

  const signed char parser::yytable_ninf_ = -5;

  const short int
  parser::yypact_[] =
  {
      45,    52,   192,   -83,   -83,   -83,    49,   -83,   -83,    89,
     123,    97,    69,   132,   123,   -83,   116,   145,   -83,   160,
     -83,   232,   116,   202,   200,   -83,   189,   189,   238,   238,
     238,   -83,   148,   142,   154,   -83,    -5,   157,   164,    88,
     -83,    39,   -83,   -83,   200,   200,   200,   -83,   165,   -83,
      98,   180,   224,   189,   189,   171,   -83,     2,   -83,   191,
     -83,   -83,   -83,   124,     4,    74,   -83,   140,    46,   -83,
     232,   -83,   238,   238,   238,   238,   238,   238,   -83,   200,
      66,   -83,   -83,   173,   175,   200,   200,   -83,    63,   156,
     138,   -83,   200,   200,   -83,   -83,   -83,   -83,   -83,   200,
     -83,   200,   200,   200,   200,   200,   -83,   -83,   -83,    62,
      47,     5,   122,   189,   189,   -83,   189,   189,   -83,   238,
     -83,   189,   189,   -83,   -83,    14,   241,   187,   187,   187,
     187,   241,   -83,   210,   -83,     9,   -10,   170,   170,    17,
     -83,   105,   -83,   -83,    76,   260,   193,   193,   193,   193,
     260,   170,   232,   -83,   -83,   -83,   178,    87,   -83,   199,
     -83,   199,   154,    83,   194,   -83,   -83,   181,   197,   210,
     209,   200,   229,   -83,   -83,   -83,   203,   189,   233,   -83,
     207,   222,   103,   218,   170,   200,   228,   -83,     3,   248,
     -83,   256,   244,   268,   170,   -83,     3,   258,   118,   243,
     218,   247,   -83,   110,   246,     3,     3,   267,   278,   -83,
     -83,   -83,   -83,   285,   252,   -83,   262,   264,   263,   -83
  };

  const unsigned char
  parser::yydefact_[] =
  {
       6,     0,     0,     1,    11,    40,     0,     5,     7,     0,
       0,     9,    38,     0,     0,    47,     0,     0,    10,     0,
      39,     0,     0,    45,     0,     3,     0,     0,     0,     0,
       0,    74,    73,     0,    63,     2,     0,     0,     0,    55,
      46,     0,    53,    54,     0,     0,     0,    88,    87,    89,
      99,     0,     0,     0,     0,    73,    16,     0,    13,    14,
      24,    15,    17,     0,    43,     0,    73,     0,     0,    71,
       0,     8,     0,     0,     0,     0,     0,     0,    52,     0,
       0,   101,    62,     0,     0,     0,     0,    48,     0,     0,
       0,    84,     0,     0,    97,    95,    93,    96,    94,     0,
      98,     0,     0,     0,     0,     0,   106,    37,    76,     0,
       0,     0,     0,     0,     0,    12,     0,     0,    23,     0,
      42,     0,     0,    72,    75,     0,    65,    67,    69,    70,
      68,    66,   102,     0,    51,     0,     0,    58,    91,     0,
      49,     0,    86,    90,     0,    78,    80,    82,    83,    81,
      79,   100,     0,    36,    25,    21,    34,     0,    33,    18,
      19,    20,    22,    44,     0,    64,    61,     0,     0,     0,
       0,     0,    56,    50,    85,    77,     0,     0,    26,    41,
       0,     0,     0,     0,    92,     0,     0,    32,     0,     0,
      59,     0,     0,     0,    57,    35,     0,     0,    27,     0,
       0,     0,   104,     0,     0,     0,     0,     0,     0,   105,
      31,    28,    30,    29,     0,   103,     0,     0,     0,    60
  };

  const short int
  parser::yypgoto_[] =
  {
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -22,   -83,
     -83,   239,   -83,    20,   -83,   120,   -83,   290,   -83,   -83,
     -83,   286,   -83,   -83,   -83,   217,   -83,   -82,   -18,    -8,
     234,   -44,   211,   108,   -16,   169,   106,   287
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     7,     8,     9,    11,    18,   156,    58,
      59,    60,    61,   198,   157,   158,    62,    10,    12,    20,
      65,    16,    23,    40,    41,    42,    43,    80,   108,    63,
     109,    50,   139,   105,    81,    82,   193,    25
  };

  const short int
  parser::yytable_[] =
  {
      89,    90,    91,    33,    57,    64,   141,    78,    51,   114,
     169,   114,   114,    34,   115,    44,   120,    45,   167,   168,
      67,    68,    69,   170,   152,   196,   116,   171,   116,   116,
      46,   110,   111,    47,    48,    49,    79,   117,   155,   117,
     117,   137,   138,   197,    34,    -4,   112,   165,   138,   145,
     172,    87,     3,    72,   114,   146,    88,   147,   148,   149,
     150,   151,    34,   132,   126,   127,   128,   129,   130,   131,
      73,   116,   152,    74,    75,   140,   133,   154,   134,   124,
      76,    77,   117,    44,   121,    45,   171,   182,    13,   122,
     114,   153,   159,     5,   160,   161,    85,   177,    46,   163,
     164,    47,    48,    49,    79,    93,    94,   116,    19,   174,
      86,   162,    95,   133,    96,   133,   205,   173,   117,    97,
     178,    98,    99,   100,   205,   101,   102,   184,    15,    72,
     206,    72,   103,   104,   175,   119,   191,   119,   206,    17,
      21,   194,    24,   210,    34,    93,    73,    72,    73,    74,
      75,    74,    75,    26,    71,   124,    76,    77,    76,    77,
     123,    72,    99,    93,    73,   101,   102,    74,    75,    27,
      70,   143,   103,   104,    76,    77,   142,    93,    73,    83,
      99,    74,    75,   101,   102,   114,    84,    92,    76,    77,
     103,   104,   106,   113,    99,     4,     5,   101,   102,   180,
     176,   114,   116,     6,   103,   104,   179,    52,    53,    28,
      53,    54,   135,   117,    39,    75,   203,   183,   116,    36,
      44,   102,    45,   116,    30,   212,   213,    31,    55,   117,
      44,    56,    45,    37,    38,    46,   181,   185,    47,    48,
      49,    39,   188,   186,    28,    46,    29,   189,    47,    48,
      49,    79,    28,   107,    29,   190,   192,   199,    28,    30,
      29,   195,    31,    32,   200,    73,    94,    30,    74,    75,
      31,    32,    95,    30,    96,    76,    31,    66,   201,    97,
     202,    98,   207,   100,    99,   209,   211,   101,   102,   214,
     215,   205,   216,   218,   103,   217,   219,   187,   118,    14,
      22,   136,   166,   144,   125,   204,   208,     0,     0,    35
  };

  const short int
  parser::yycheck_[] =
  {
      44,    45,    46,    21,    26,    27,    88,    12,    24,     7,
      20,     7,     7,    21,    12,    20,    12,    22,     9,    10,
      28,    29,    30,    33,    10,    22,    24,    10,    24,    24,
      35,    53,    54,    38,    39,    40,    41,    35,    33,    35,
      35,    85,    86,    40,    52,     0,    54,    33,    92,    93,
      33,    12,     0,     7,     7,    99,    17,   101,   102,   103,
     104,   105,    70,    79,    72,    73,    74,    75,    76,    77,
      24,    24,    10,    27,    28,    12,    10,    30,    12,    33,
      34,    35,    35,    20,    10,    22,    10,   169,    39,    15,
       7,    29,   114,     4,   116,   117,     8,    10,    35,   121,
     122,    38,    39,    40,    41,     7,     8,    24,    39,    33,
      22,   119,    14,    10,    16,    10,     6,    12,    35,    21,
      33,    23,    24,    25,     6,    27,    28,   171,     5,     7,
      20,     7,    34,    35,   152,    13,    33,    13,    20,    42,
       8,   185,    26,    33,   152,     7,    24,     7,    24,    27,
      28,    27,    28,     8,    12,    33,    34,    35,    34,    35,
      20,     7,    24,     7,    24,    27,    28,    27,    28,     9,
      22,    33,    34,    35,    34,    35,    20,     7,    24,    22,
      24,    27,    28,    27,    28,     7,    22,    22,    34,    35,
      34,    35,    12,    22,    24,     3,     4,    27,    28,    18,
      22,     7,    24,    11,    34,    35,    12,    18,    19,    20,
      19,    22,    39,    35,    39,    28,   196,     8,    24,    17,
      20,    28,    22,    24,    35,   205,   206,    38,    39,    35,
      20,    42,    22,    31,    32,    35,    39,     8,    38,    39,
      40,    39,     9,    40,    20,    35,    22,    40,    38,    39,
      40,    41,    20,    29,    22,    33,    38,     9,    20,    35,
      22,    33,    38,    39,     8,    24,     8,    35,    27,    28,
      38,    39,    14,    35,    16,    34,    38,    39,    34,    21,
      12,    23,    39,    25,    24,    38,    40,    27,    28,    22,
      12,     6,    40,    29,    34,    33,    33,   177,    59,     9,
      14,    84,   133,    92,    70,   197,   200,    -1,    -1,    22
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    44,    45,     0,     3,     4,    11,    46,    47,    48,
      60,    49,    61,    39,    60,     5,    64,    42,    50,    39,
      62,     8,    64,    65,    26,    80,     8,     9,    20,    22,
      35,    38,    39,    71,    72,    80,    17,    31,    32,    39,
      66,    67,    68,    69,    20,    22,    35,    38,    39,    40,
      74,    77,    18,    19,    22,    39,    42,    51,    52,    53,
      54,    55,    59,    72,    51,    63,    39,    72,    72,    72,
      22,    12,     7,    24,    27,    28,    34,    35,    12,    41,
      70,    77,    78,    22,    22,     8,    22,    12,    17,    74,
      74,    74,    22,     7,     8,    14,    16,    21,    23,    24,
      25,    27,    28,    34,    35,    76,    12,    29,    71,    73,
      51,    51,    72,    22,     7,    12,    24,    35,    54,    13,
      12,    10,    15,    20,    33,    73,    72,    72,    72,    72,
      72,    72,    77,    10,    12,    39,    68,    74,    74,    75,
      12,    70,    20,    33,    75,    74,    74,    74,    74,    74,
      74,    74,    10,    29,    30,    33,    51,    57,    58,    51,
      51,    51,    72,    51,    51,    33,    78,     9,    10,    20,
      33,    10,    33,    12,    33,    71,    22,    10,    33,    12,
      18,    39,    70,     8,    74,     8,    40,    58,     9,    40,
      33,    33,    38,    79,    74,    33,    22,    40,    56,     9,
       8,    34,    12,    56,    76,     6,    20,    39,    79,    38,
      33,    40,    56,    56,    22,    12,    40,    33,    29,    33
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    43,    44,    44,    44,    45,    45,    46,    47,    48,
      49,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    53,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    61,
      61,    62,    62,    63,    63,    64,    65,    65,    66,    66,
      66,    66,    66,    67,    67,    68,    68,    68,    68,    69,
      69,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    77,
      77,    78,    78,    66,    66,    79,    80
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     5,     4,     0,     2,     0,     1,     5,     2,
       2,     0,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     1,     3,     4,     6,     3,     3,
       3,     3,     3,     1,     1,     4,     3,     2,     2,     2,
       0,     6,     4,     1,     3,     2,     2,     0,     2,     3,
       4,     3,     2,     1,     1,     1,     4,     6,     3,     6,
      13,     3,     1,     1,     4,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     4,     3,     1,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     9,     7,     3,     3
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
  "\"?\"", "\"\\\\\"", "\"^\"", "\"}\"", "\"]\"", "\"random\"", "\"pr\"",
  "\")\"", "\"/\"", "\"-\"", "UBNOT", "UMINUS", "\"<NUMBER>\"",
  "\"<IDENTIFIER>\"", "\"<VARIABLE>\"", "\"not\"", "\"<SORT_NAME>\"",
  "$accept", "program", "directives", "directive", "const_decl",
  "sorts_sec", "sort_defs", "sort_def", "sort_expr", "range",
  "concatenation", "concat_elem", "functional_symbol", "cond",
  "var_sort_expr_list", "var_sort_expr", "curly_brackets", "atts_sec",
  "att_defs", "att_def", "sort_expr_vec", "stmts_sec", "stmts", "stmt",
  "head", "head_atom", "random_atom", "body", "constterm",
  "comparable_constterm", "consttermvec", "term", "ntermvec", "cmp",
  "literal", "e_literal", "probability", "query", YY_NULLPTR
  };

#if PLOGGRAMMAR_DEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,   192,   192,   193,   193,   203,   204,   207,   211,   220,
     223,   224,   227,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   242,   245,   246,   249,   252,   254,   258,   259,
     260,   261,   267,   268,   271,   272,   275,   276,   283,   285,
     286,   289,   290,   293,   294,   302,   305,   306,   313,   314,
     315,   316,   317,   321,   322,   326,   327,   328,   329,   332,
     333,   339,   340,   345,   346,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   366,   367,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   393,   394,   402,   403,   404,   405,   406,   407,   410,
     411,   414,   415,   419,   420,   423,   426
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
#line 1758 "ploggrammar.tab.cc" // lalr1.cc:1167
