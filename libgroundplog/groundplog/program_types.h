//
// Created by iensen on 8/17/16.
//

#ifndef PLOG_PROGRAM_TYPES_H
#define PLOG_PROGRAM_TYPES_H
#include<groundplog/util/platform.h>
#include <assert.h>
#include <groundplog/literal.h>
#include<vector>

namespace GroundPlog {

    class Program;
    typedef uint32 AttId;
    typedef uint32 ValueRep;
    typedef uint32 Var;

    struct Atom_t {
        AttId attid;
        ValueRep valid;
    };

    struct Lit_t {
        AttId attid;
        ValueRep valid;
        bool defaultNeg;
        bool classicNeg;
    };


    typedef uint64 Id_t;
      //! A variable is an integer in the range [0..varMax).


    //! Possible types of a variable.
    struct Var_t {
        enum Type { Atom = 1, Body = 2, Hybrid = Atom | Body};
        static bool isBody(Type t) {
            return (static_cast<uint32>(t) & static_cast<uint32>(Body)) != 0;
        }
        static bool isAtom(Type t) {
            return (static_cast<uint32>(t) & static_cast<uint32>(Atom)) != 0;
        }
    };
    typedef Var_t::Type VarType;


//! Stores static information about a variable.
    struct VarInfo {
        enum Flag {
            Mark_p = 0x1u,  // mark for positive literal
            Mark_n = 0x2u,  // mark for negative literal
            Body   = 0x8u,  // is this var representing a body?
        };
        static uint8 flags(VarType t) {
            if (t == Var_t::Body)  { return VarInfo::Body; }
            return 0;
        }
        explicit VarInfo(uint8 r = 0) : rep(r) { }
        //! Returns the type of the variable (or Var_t::Hybrid if variable was created with parameter eq=true).
        VarType type()          const { return  VarType(Var_t::Atom + has(VarInfo::Body)); }

        bool    has(Flag f)     const { return (rep & flag(f)) != 0; }
        bool    has(uint32 f)   const { return (rep & f) != 0;       }
        bool    hasAll(uint32 f)const { return (rep & f) == f; }
        void    set(Flag f)           { rep |= flag(f); }
        void    toggle(Flag f)        { rep ^= flag(f); }
        static uint8 flag(Flag x)     { return uint8(x); }
        uint8 rep;
    };



    struct Rule {
        Atom_t head;
        std::vector<Lit_t> body;
    };

    struct RandomRule {
        std::vector<std::pair<Atom_t,AttId>>  head;
        std::vector<Lit_t> body;
    };

    struct PrAtom {
        Atom_t head;
        std::vector<Lit_t> body;
    };



//! A node of a program-dependency graph.
/*!
 * A node represents a relevant part in a logic program. Each node
 * has at least a literal and a value.
 */
    class PrgNode {
    public:
        //! Supported node types.
        enum Type {
            Atom = 0u, Body = 1u
        };
        static const uint32 noScc = (1u << 27) - 1;
        static const uint32 noNode = (1u << 28) - 1;
        static const uint32 noLit = 1;

        //! Creates a new node that corresponds to a literal that is false.
        explicit PrgNode(uint32 id, bool checkScc = true);



        //! Returns true if node has an associated variable in a solver.
        bool hasVar() const { return litId_ != noLit; }

        //! Returns the literal associated with this node or a sentinel literal if no var is associated with this node.
        Literal literal() const { return Literal::fromId(litId_); }

        //! Returns the value currently assigned to this node.
        ValueRep value() const { return val_; }

        //! Returns the current id of this node.
        uint32 id() const { return id_; }

        void setValue(ValueRep v) { val_ = v; }


    protected:
        uint32 litId_ : 31; // literal-id in solver
        uint32 id_    : 28; // own id/eq-id/root-id/ufs-id
        uint32 val_   :  2; // assigned value


        void resetId(uint32 id, bool seen) {
            id_ = id;
        }

        //@}
    private:
        PrgNode(const PrgNode &);

        PrgNode &operator=(const PrgNode &);
    };

    typedef PrgNode::Type NodeType;
//! An edge of a program-dependency graph.
/*!
 * Currently, plog distinguishes four types of edges:
 *  - a Normal edge stipulates an implication between body and head,
 */
    struct PrgEdge {
        //! Type of edge.
        enum Type {
            Normal = 0
        };

        static PrgEdge noEdge() {
            PrgEdge x;
            x.rep = UINT32_MAX;
            return x;
        }

        template<class NT>
        static PrgEdge newEdge(const NT &n, Type eType) {
            // 28-bit node id, 2-bit node type, 2-bit edge type
            PrgEdge x = {(n.id() << 4) | (static_cast<uint32>(n.nodeType()) << 2) | eType};
            return x;
        }

        //! Returns the id of the adjacent node.
        uint32 node() const { return rep >> 4; }

        //! Returns the type of this edge.
        Type type() const { return Type(rep & 3u); }

        //! Returns the type of adjacent node.
        NodeType nodeType() const { return NodeType((rep >> 2) & 3u); }


        //! Returns true if the adjacent node is a body.
        bool isBody() const { return nodeType() == PrgNode::Body; }

        //! Returns true if the adjacant node is an atom.
        bool isAtom() const { return nodeType() == PrgNode::Atom; }


        bool operator<(PrgEdge rhs) const { return rep < rhs.rep; }

        bool operator==(PrgEdge rhs) const { return rep == rhs.rep; }

        uint32 rep;
    };

    typedef PrgEdge::Type EdgeType;

    class PrgHead : public PrgNode {
    public:

        typedef  std::vector<PrgEdge>::const_iterator sup_iterator;
        //! Is this head an atom?
        bool isAtom() const { return isAtom_ != 0; }

        //! Number of supports (rules) for this head.
        uint32 supports() const { return supports_.size(); }

        sup_iterator supps_begin() const { return supports_.begin(); }

        sup_iterator supps_end() const { return supports_.end(); }

        //! External atom (or defined in a later incremental step)?
        bool frozen() const { return freeze_ != uint32(freeze_no); }


        //! Adds r as support edge for this node.
        void addSupport(PrgEdge r) { throw "not implemented"; }


        //! Assigns the value v to this head.
        bool assignValue(ValueRep v) { throw "not implemented"; }

        NodeType nodeType() const { return isAtom() ? PrgNode::Atom : PrgNode::Body; }
        //@}
    protected:
        enum FreezeState {
            freeze_no = 0u, freeze_free = 1u, freeze_true = 2u, freeze_false = 3u
        };

        //! Creates a new node that corresponds to a literal that is false.
        explicit PrgHead(uint32 id, NodeType t, uint32 data = 0, bool checkScc = true);


        std::vector<PrgEdge> supports_;  // possible supports (body or disjunction)
        uint32 data_  : 27; // number of atoms in disjunction or scc of atom
        uint32 upper_ :  1; // in (simplified) program?
        uint32 dirty_ :  1; // is list of supports dirty?
        uint32 freeze_:  2; // incremental freeze state
        uint32 isAtom_:  1; // is this head an atom?
    };



    class PrgAtom : public PrgHead {
    public:
        enum Dependency { dep_pos = 0, dep_neg = 1, dep_all = 2 };
        typedef std::vector<Lit_t>::const_iterator dep_iterator;
        explicit PrgAtom(uint32 id, bool checkScc = true);
        NodeType     nodeType() const { return PrgNode::Atom; }
        /*!
         * \name forward dependencies (bodies containing this atom)
         */
        //@{
        dep_iterator deps_begin()                   const { return deps_.begin(); }
        dep_iterator deps_end()                     const { return deps_.end();   }
        bool         hasDep(Dependency d)           const;
        void         addDep(Id_t bodyId, bool pos);
        void         removeDep(Id_t bodyId, bool pos);
        void         clearDeps(Dependency d);
        //@}
  private:
        std::vector<Lit_t> deps_; // bodies depending on this atom
    };

//! A (rule) body in a logic program.
    class PrgBody : public PrgNode {
    public:


        //! Creates a new body node and connects the node to its predecessors.
        /*!
         * \param prg     The program in which the new body is used.
         * \param id      The id for the new body node.
         * \param rule    The rule for which a body node is to be created.
         * \param pos     Positive body size.
         * \param addDeps If true, add an edge between each atom subgoal and the new node.
         */
        static PrgBody* create(Program& prg, uint32 id, const Rule& rule, uint32 pos, bool addDeps);
        //! Returns the number of atoms in the body.
        uint32   size()  const { return size_; }
        /*!
         * A normal body is supported, iff all of its positive subgoals are supported.
         * A count/sum body is supported if the sum of the weights of the supported positive +
         * the sum of the negative weights is >= lowerBound().
         */
        bool     isSupported() const { throw ; }
        //! Returns true if this body defines any head.
        bool     hasHeads()    const { throw "not implemented"; }
        //! Destroys a body node created via create().
        void     destroy();
        //! Adds a rule edge between this body and the given head.
        /*!
         * \note
         *   The function also adds a corresponding back edge to the head.
         * \note
         *   Adding a head invalidates the set property for the heads of this body.
         *   To restore it, call simplifyHeads()
         */
        void     addHead(PrgHead* h, EdgeType t);
        //! Simplifies the heads of this body and establishes set property.
        /*!
         * Removes superfluous heads and sets the body to false if for some atom a
         * in the head of this body B, Ta -> FB. In that case, all heads atoms are removed, because
         * a false body can't define any atom.
         * If strong is true, removes head atoms that are not associated with a variable.
         * \return
         *    setValue(value_false) if setting a head of this body to true would
         *    make the body false (i.e. the body is a selfblocker). Otherwise, true.
         */
        //! Propagates the assignment of subgoal p.
        bool     propagateAssigned(Program& prg, Literal p, ValueRep v);
        //! Propagates the assignment of a head.
        bool     propagateAssigned(Program& prg, PrgHead* h, EdgeType t);
        //! Propagates the value of this body.
        bool     propagateValue(Program& prg, bool backprop);
        bool     propagateValue(Program& prg);
        NodeType nodeType() const  { return PrgNode::Body; }
    private:
        static const uint32 maxSize = (1u<<26)-1;
        typedef unsigned char byte_t;
        struct Norm { Literal lits[0]; };
        PrgBody(uint32 id, Program& prg, const std::vector<Lit_t>& lits, uint32 pos, bool addDeps);
        ~PrgBody();
        uint32   findLit(const Program& prg, Literal p) const;
        void     addHead(PrgEdge h);
        bool     eraseHead(PrgEdge h);
        std::vector<Lit_t>  body;
        uint32    size_   : 25; // |B|
        uint32    head_   :  2; // simple or extended head?
        uint32    type_   :  2; // body type
        uint32    sBody_  :  1; // simplify body?
        uint32    sHead_  :  1; // simplify head?
        uint32    freeze_ :  1; // keep body even if it does not occur in a rule?

     };



}



#endif //PLOG_PROGRAM_TYPES_H
