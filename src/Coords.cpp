#include "Coords.h"

namespace min2phase { namespace Coords {
        /**
         * In this array are stored the cubes result from each possible move
         * from a solved cube. The motion of the corner and edges moved from
         * one of the 18 move is constant. So, we can use basic cubes with the
         * scramble generated from the 18 moves of the cube. In this way,
         * whe can make a multiplication of a cube and a basic move to get
         * a new cube. This increase the speed of the algorithm.
         */
        CubieCube moveCube[CubeInfo::N_MOVES]{};

        //symmetry
        /**
         * In this array are stored the symmetries generated by S_F2, S_U4
         * and S_LR2. To increase the speed of algorithm, we use the symmetries.
         * You can read the complete definition in the Kociemba's page.
         * If you apply F to the cube x1 and R to x2, the two cube are the same
         * because if you rotate x1, you get x2. This increase the speed of the algorithm.
         */
        CubieCube CubeSym[CubeInfo::SYM];

        long moveCubeSym[CubeInfo::N_MOVES] = {0};//TODO

        /**
         * This matrix is used to convert symmetry index into one symmetry for the CubeSym.
         */
        int8_t SymMult[CubeInfo::SYM][CubeInfo::SYM] = {0};

        /**
         * This matrix is used to convert Symmetry for CubeSym into symmetry index.
         */
        int8_t SymMultInv[CubeInfo::SYM][CubeInfo::SYM] = {0};

        int8_t SymMove[CubeInfo::SYM][CubeInfo::N_MOVES] = {0};//TODO
        int8_t Sym8Move[8 * CubeInfo::N_MOVES] = {0};//TODO
        int8_t SymMoveUD[CubeInfo::SYM][CubeInfo::N_MOVES] = {0};//TODO

        /**
         * This is used to convert the middle slice perm.
         */
        int8_t MPermInv[CubeInfo::N_MPERM] = {0};

        /**
         * This is used to convert the permutation into corner comb.
         */
        int8_t Perm2CombP[CubeInfo::N_PERM_SYM] = {0};

        /**
         * This is used to convert a symmetry index into a permutation of edges or corner.
         */
        unsigned short PermInvEdgeSym[CubeInfo::N_PERM_SYM] = {0};


        /**
         * Raw-Coordinate to Sym-Coordinate.
         * This type of coordinate are used to convert a normal coordinate of the
         * cube into his symmetry. We can compute the corresponding symmetry of a
         * coordinate every time but it's too slow.
         */

        /**
         * This is used to converts the edge or corner perm into the symmetry.
         * sym = EPermR2S[ edge perm]
         * sym = E2C(EPermR2S[corner perm])
         */
        unsigned short EPermR2S[CubeInfo::N_PERM] = {0};

        /**
         * This is used to converts the edge orientation into the symmetry.
         * sym = FlipR2S[ edge orientation ]
         */
        unsigned short FlipR2S[CubeInfo::N_FLIP] = {0};

        /**
         * This is used to converts the corner orientation into the symmetry.
         * sym = TwistR2S[ corner orientation ]
         */
        unsigned short TwistR2S[CubeInfo::N_TWIST] = {0};

        /**
         * This is used to converts the symmetry into the edge orientation.
         * sym = FlipS2RF[ symmetry ]
         */
        unsigned short FlipS2RF[CubeInfo::N_FLIP_SYM * CubeInfo::SYM_CLASSES] = {0};

        /**
         * Below there are the coordinate used in phase 1 and 2 (see Kociemba's algorithm).
         * The coordinate XMove indicates the moving table for every coordinate. If you have
         * a cube and rotate a face, the coordinate changes, this matrix help to get the new
         * coordinate immediately.
         * The coordinate with XPrun indicate the table used to get the pruning value from each
         * coordinate.
         * the XConj coordinate indicates the Table used for symmetries.
         */

        ///phase1 coords

        /**
         * This matrix contains the moving table for the edge orientation.
         */
        unsigned short FlipMove[CubeInfo::N_FLIP_SYM][CubeInfo::N_MOVES] = {0};

        /**
         * This matrix contains the moving table for the corner orientation.
         */
        unsigned short TwistMove[CubeInfo::N_TWIST_SYM][CubeInfo::N_MOVES] = {0};

        /**
         * This matrix contains the moving table for the UDSlice coordinate.
         */
        unsigned short UDSliceMove[CubeInfo::N_SLICE][CubeInfo::N_MOVES] = {0};

        /**
         * This matrix contains the moving table for the symmetry in phase 1.
         */
        unsigned short UDSliceConj[CubeInfo::N_SLICE][CubeInfo::SYM_CLASSES] = {0};

        /**
         * This matrix contains the pruning table for the UDsliceTwist coordinate.
         */
        int UDSliceTwistPrun[CubeInfo::N_SLICE*CubeInfo::N_TWIST_SYM/CubeInfo::SYM_CLASSES+1] = {0};

        /**
         * This matrix contains the pruning table for the UDsliceFlip coordinate.
         */
        int UDSliceFlipPrun[CubeInfo::N_SLICE*CubeInfo::N_FLIP_SYM/CubeInfo::SYM_CLASSES+1] = {0};

        /**
         * This matrix contains the pruning table for the edge and corner orientation coordinate.
         */
        int TwistFlipPrun[CubeInfo::N_FLIP*CubeInfo::N_TWIST_SYM/CubeInfo::SYM_CLASSES+1] = {0};

        ///phase 2 coords

        /**
         * This matrix contains the moving table for the corner permutation.
         */
        unsigned short CPermMove[CubeInfo::N_PERM_SYM][CubeInfo::N_MOVES2] = {0};

        /**
         * This matrix contains the moving table for the edge permutation.
         */
        unsigned short EPermMove[CubeInfo::N_PERM_SYM][CubeInfo::N_MOVES2] = {0};

        /**
         * This matrix contains the moving table for the UDSliceSorted permutation.
         */
        uint8_t MPermMove[CubeInfo::N_MPERM][CubeInfo::N_MOVES2] = {0};

        /**
         * This matrix contains the moving table for the corner comb permutation.
         */
        uint8_t CCombPMove[CubeInfo::N_COMB][CubeInfo::N_MOVES2] = {0};

        /**
         * This matrix contains the moving table for the symmetry of UDSliceSorted.
         */
        uint8_t MPermConj[CubeInfo::N_MPERM][CubeInfo::SYM] = {0};

        /**
         * This matrix contains the moving table for the symmetry of corner perm in the upper slice.
         */
        uint8_t CCombPConj[CubeInfo::N_COMB][CubeInfo::SYM] = {0};

        /**
         * This matrix contains the pruning table for the edge permutation coordinate.
         */
        int MCPermPrun[CubeInfo::N_MPERM * CubeInfo::N_PERM_SYM/CubeInfo::SYM_CLASSES+1] = {0};

        /**
         * This matrix contains the pruning table for the corner permutation coordinate.
         */
        int EPermCCombPPrun[CubeInfo::N_COMB * CubeInfo::N_PERM_SYM/CubeInfo::SYM_CLASSES+1] = {0};


        /**
         * This the S_URF symmetry that make a rotation of 120 degree of the cube around
         * an axis through the URF-corner and DBL-corner,
         * See Kociemba's algorithm Equivalent Cubes and Symmetry.
         */
        CubieCube urf{};

        /**
         * This the S_URF^-1 symmetry that make a rotation of -120 degree of the cube around
         * an axis through the URF-corner and DBL-corner,
         * See Kociemba's algorithm Equivalent Cubes and Symmetry.
         */
        CubieCube urfInv{};

        /**
     * The edge perm and corner perm have the same symmetry structure.
     * So their ClassIndexToRepresentArray (see Kociemba's algorithm) are the same.
     * So, when you want the symmetry of edge permutation you do y*16+k, where
     * y is the edge permutation.
     * Otherwise, if you need the symmetry of corner permutation you do
     * y*16+(k^e2c[k]) where y is the corner orientation.
     *
     * This is e2c.
     */
    static const int SYM_E2C_MAGIC = 0x00DDDD00;

    /**
     * This indicates if the coordinates and symmetries are initialized.
     */
    static bool isInitialized = false;

    ///ClassIndexToRepresentArrays

    /**
     * This is used to convert the raw symmetry to raw coordinate
     * of edge orientation.
     * Used only in the coordinate computation.
     * This is temporary.
     */
    static unsigned short FlipS2R[CubeInfo::N_FLIP_SYM];

    /**
     * This is used to convert the raw symmetry to raw coordinate
     * of corner orientation.
     * Used only in the coordinate computation.
     * This is temporary.
     */
    static unsigned short TwistS2R[CubeInfo::N_TWIST_SYM];

    /**
     * This is used to convert the raw symmetry to raw coordinate of
     * edge and corner orientation.
     * Used only in the coordinate computation.
     * This is temporary.
     */
    static unsigned short EPermS2R[CubeInfo::N_PERM_SYM];

    ///Symmetries

    /**
     * This is a temporary array used to compute the symmetry state of edge orientation.
     */
    static unsigned short SymStateTwist[CubeInfo::N_TWIST_SYM];

    /**
     * This is a temporary array used to compute the symmetry state for corner orientation.
     */
    static unsigned short SymStateFlip[CubeInfo::N_FLIP_SYM];

    /**
     * This is a temporary array used to compute the symmetry state for permutations.
     */
    static unsigned short SymStatePerm [CubeInfo::N_PERM_SYM];

    //init all coordinates
    void init() {
        urf.setValues(2531, 1373, 67026819, 1367);
        urfInv.setValues(2089, 1906, 322752913, 2040);

        initMove();
        initSym();
        initPermSym2Raw();

        initPermsMove();
        initMPermMoveConj();
        initCombPMoveConj();

        initFlipMove();
        initTwistMove();
        initUDSliceMoveConj();

        initAllPrun();

        isInitialized = true;
    }

    bool isInit() {
        return isInitialized;
    }

    //b = S_idx^-1 * a * S_idx for only corner
    void CornConjugate(const CubieCube &a, int8_t idx, CubieCube &b) {
        int8_t oriA, oriB, corn, ori;
        CubieCube sinv, s;

        sinv.setValues(CubeSym[SymMultInv[0][idx]]);
        s.setValues(CubeSym[idx]);

        for (corn = 0; corn < CubeInfo::NUMBER_CORNER; corn++) {
            oriA = sinv.corners[a.corners[s.corners[corn] & 7] & 7] >> CubeInfo::CORNE_ORI_CASES;
            oriB = a.corners[s.corners[corn] & 7] >> CubeInfo::CORNE_ORI_CASES;
            ori = (oriA < CubeInfo::CORNE_ORI_CASES) ? oriB : (CubeInfo::CORNE_ORI_CASES - oriB) %
                                                              CubeInfo::CORNE_ORI_CASES;
            b.corners[corn] = sinv.corners[a.corners[s.corners[corn] & 7] & 7] & 7 | ori << CubeInfo::CORNE_ORI_CASES;
        }
    }

    //b = S_idx^-1 * a * S_idx for only edges
    void EdgeConjugate(const CubieCube &a, int8_t idx, CubieCube &b) {
        uint8_t ed;
        CubieCube sinv, s;

        sinv.setValues(CubeSym[SymMultInv[0][idx]]);
        s.setValues(CubeSym[idx]);

        for (ed = 0; ed < CubeInfo::NUMBER_EDGES; ed++)
            b.edges[ed] =
                    sinv.edges[a.edges[s.edges[ed] >> 1] >> 1] ^ (a.edges[s.edges[ed] >> 1] & 1) ^ (s.edges[ed] & 1);
    }

    //perm from sym
    unsigned short getPermSymInv(unsigned short idx, int8_t sym, bool isCorner) {
        unsigned short idxi = PermInvEdgeSym[idx];

        if (isCorner)
            idxi = ESym2CSym(idxi);

        return idxi & 0xfff0 | SymMult[idxi & 0xf][sym];
    }

    //check if two cubes are the same
    bool isSameCube(const int8_t cube1[], const int8_t cube2[], bool isEdge) {
        const int8_t len = isEdge ? CubeInfo::NUMBER_EDGES : CubeInfo::NUMBER_CORNER;
        int8_t i;

        for (i = 0; i < len; i++)
            if (cube1[i] != cube2[i])
                return false;

        return true;
    }

    //y*16+(k^e2c[k])
    int ESym2CSym(unsigned short idx) {
        return idx ^ (SYM_E2C_MAGIC >> ((idx & 0xf) << 1) & 3);
    }

    //set value in pruning table
    void setPruning(int table[], int index, int8_t value) {
        table[index >> 3] ^= value << (index << 2); // index << 2 <=> (index & 7) << 2
    }

    //get value in pruning table
    int8_t getPruning(const int table[], int index) {
        return table[index >> 3] >> (index << 2) & 0xf; // index << 2 <=> (index & 7) << 2
    }

    bool hasZero(int val) {
        return ((val - 0x11111111) & ~val & 0x88888888) != 0;
    }

    //rotation a b c
    void rotateCube(CubieCube &a, CubieCube &b, CubieCube &d) {
        CubieCube &tmp = a;

        a = b;
        b = d;
        d = tmp;
    }

    //init basic 18 moves
    void initMove() {
        const short cPermSon[CubeInfo::N_BASIC_MOVES] = {15120, 21021, 8064, 9, 1230, 224};
        const short cOriSon[CubeInfo::N_BASIC_MOVES] = {0, 1494, 1236, 0, 412, 137};
        const int ePermSon[CubeInfo::N_BASIC_MOVES] = {119750400, 323403417, 29441808, 5880, 2949660, 328552};
        const short eOriSon[CubeInfo::N_BASIC_MOVES] = {0, 0, 550, 0, 0, 137};
        uint8_t i, j;

        for (i = 0; i < CubeInfo::N_MOVES; i += CubeInfo::N_GROUP_MOVES)
            moveCube[i].setValues(cPermSon[i / 3], cOriSon[i / 3], ePermSon[i / 3], eOriSon[i / 3]);

        for (i = 0; i < CubeInfo::N_MOVES; i += CubeInfo::N_GROUP_MOVES) {
            for (j = 0; j < CubeInfo::N_GROUP_MOVES - 1; j++) {
                CubieCube::EdgeMult(moveCube[i + j], moveCube[i], moveCube[i + j + 1]);
                CubieCube::CornMult(moveCube[i + j], moveCube[i], moveCube[i + j + 1]);
            }
        }
    }

    //init all sym
    void initSym() {
        unsigned short i;
        uint8_t j, k;

        CubieCube t, c, d, f2, u4, lr2;

        f2.setValues(28783, 0, 259268407, 0);
        u4.setValues(15138, 0, 119765538, 7);
        lr2.setValues(5167, 0, 83473207, 0);

        for (i = 0; i < CubeInfo::NUMBER_CORNER; i++)
            lr2.corners[i] |= CubeInfo::CORNE_ORI_CASES << CubeInfo::CORNE_ORI_CASES;

        for (i = 0; i < CubeInfo::SYM; i++) {
            CubeSym[i].setValues(c);

            CubieCube::CornMultFull(c, u4, d);
            CubieCube::EdgeMult(c, u4, d);
            rotateCube(t, d, c);

            if (i % 4 == 3) {
                CubieCube::CornMultFull(c, lr2, d);
                CubieCube::EdgeMult(c, lr2, d);
                rotateCube(t, d, c);
            }

            if (i % 8 == 7) {
                CubieCube::CornMultFull(c, f2, d);
                CubieCube::EdgeMult(c, f2, d);
                rotateCube(t, d, c);
            }
        }

        for (i = 0; i < CubeInfo::SYM; i++) {
            for (j = 0; j < CubeInfo::SYM; j++) {
                CubieCube::CornMultFull(CubeSym[i], CubeSym[j], c);

                for (k = 0; k < CubeInfo::SYM; k++) {
                    if (isSameCube(CubeSym[k].corners, c.corners, false)) {
                        SymMult[i][j] = k;
                        SymMultInv[k][j] = i;
                        break;
                    }
                }
            }
        }

        for (i = 0; i < CubeInfo::N_MOVES; i++) {
            for (j = 0; j < CubeInfo::SYM; j++) {
                CornConjugate(moveCube[i], SymMultInv[0][j], c);

                for (k = 0; k < CubeInfo::N_MOVES; k++) {
                    if (isSameCube(moveCube[k].corners, c.corners, false)) {
                        SymMove[j][i] = k;
                        SymMoveUD[j][CubeInfo::std2ud[i]] = CubeInfo::std2ud[k];
                        break;
                    }
                }

                if (j % 2 == 0)
                    Sym8Move[i << 3 | j >> 1] = SymMove[j][i];
            }

            moveCubeSym[i] = moveCube[i].selfSymmetry();
        }
    }

    //raw coordinate = transformation array[symmetry]
    void initPermSym2Raw() {
        short i;
        CubieCube cc;

        initSym2Raw(CubeInfo::N_PERM, EPermS2R, EPermR2S, SymStatePerm, EPERM_TYPE);

        for (i = 0; i < CubeInfo::N_PERM_SYM; i++) {
            cc.setEPerm(EPermS2R[i]);
            Perm2CombP[i] = CubieCube::getComb(cc.edges, 0, true) +
                            CubieCube::getNParity(EPermS2R[i], CubeInfo::NUMBER_CORNER) * 70;
            cc.invCubieCube();
            PermInvEdgeSym[i] = cc.getEPermSym();
        }

        for (i = 0; i < CubeInfo::N_MPERM; i++) {
            cc.setMPerm(i);
            cc.invCubieCube();
            MPermInv[i] = cc.getMPerm();
        }

        initSym2Raw(CubeInfo::N_FLIP, FlipS2R, FlipR2S, SymStateFlip, FLIP_TYPE);
        initSym2Raw(CubeInfo::N_TWIST, TwistS2R, TwistR2S, SymStateTwist, TWIST_TYPE);
    }

    //raw coordinate = transformation array[symmetry].
    void initSym2Raw(const unsigned short N_RAW, unsigned short Sym2Raw[], unsigned short Raw2Sym[],
                                            unsigned short SymState[], const CoordType &coord) {
        CubieCube c, d;
        const uint8_t symInc = coord == EPERM_TYPE ? 1 : 2;
        const bool isEdge = coord != TWIST_TYPE;
        unsigned short i, symIdx, idx, count;
        uint8_t j;

        idx = 0;
        count = 0;

        for (i = 0; i < N_RAW; i++)
            Raw2Sym[i] = 0;

        for (i = 0; i < N_RAW; i++) {
            if (Raw2Sym[i] != 0)
                continue;

            switch (coord) {
                case FLIP_TYPE:
                    c.setFlip(i);
                    break;
                case TWIST_TYPE:
                    c.setTwist(i);
                    break;
                case EPERM_TYPE:
                    c.setEPerm(i);
                    break;
                default:
                    break;
            }

            for (j = 0; j < CubeInfo::SYM; j += symInc) {
                if (isEdge)
                    EdgeConjugate(c, j, d);
                else
                    CornConjugate(c, j, d);

                switch (coord) {
                    case FLIP_TYPE:
                        idx = d.getFlip();
                        FlipS2RF[count << 3 | j >> 1] = idx;
                        break;
                    case TWIST_TYPE:
                        idx = d.getTwist();
                        break;
                    case EPERM_TYPE:
                        idx = d.getEPerm();
                        break;
                    default:
                        break;
                }

                if (idx == i)
                    SymState[count] |= 1 << (j / symInc);

                symIdx = (count << 4 | j) / symInc;
                Raw2Sym[idx] = symIdx;
            }
            Sym2Raw[count++] = i;
        }
    }

    //Corner and Edge permutation table
    void initPermsMove() {
        unsigned short i;
        uint8_t j;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_PERM_SYM; i++) {
            c.setCPerm(EPermS2R[i]);
            c.setEPerm(EPermS2R[i]);

            for (j = 0; j < CubeInfo::N_MOVES2; j++) {
                CubieCube::CornMult(c, moveCube[CubeInfo::ud2std[j]], d);
                CPermMove[i][j] = d.getCPermSym();

                CubieCube::EdgeMult(c, moveCube[CubeInfo::ud2std[j]], d);
                EPermMove[i][j] = d.getEPermSym();
            }
        }
    }

    //UDSlice sorted move table
    void initMPermMoveConj() {
        uint8_t i, j;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_MPERM; i++) {
            c.setMPerm(i);

            for (j = 0; j < CubeInfo::N_MOVES2; j++) {
                CubieCube::EdgeMult(c, moveCube[CubeInfo::ud2std[j]], d);
                MPermMove[i][j] = d.getMPerm();
            }

            for (j = 0; j < CubeInfo::SYM; j++) {
                EdgeConjugate(c, SymMultInv[0][j], d);
                MPermConj[i][j] = d.getMPerm();
            }
        }
    }

    //Corner comb move table
    void initCombPMoveConj() {
        uint8_t i, j;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_COMB; i++) {
            c.setCComb(i % 70);

            for (j = 0; j < CubeInfo::N_MOVES2; j++) {
                CubieCube::CornMult(c, moveCube[CubeInfo::ud2std[j]], d);
                CCombPMove[i][j] = d.getCComb() + 70 * (CubeInfo::P2_PARITY_MOVE >> j & 1 ^ (i / 70));
            }

            for (j = 0; j < 16; j++) {
                CornConjugate(c, SymMultInv[0][j], d);
                CCombPConj[i][j] = d.getCComb() + 70 * (i / 70);
            }
        }
    }

    //edge orient move table
    void initFlipMove() {
        unsigned short i;
        uint8_t j;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_FLIP_SYM; i++) {
            c.setFlip(FlipS2R[i]);

            for (j = 0; j < CubeInfo::N_MOVES; j++) {
                CubieCube::EdgeMult(c, moveCube[j], d);
                FlipMove[i][j] = d.getFlipSym();
            }
        }
    }

    //corner orient move table
    void initTwistMove() {
        unsigned short i;
        uint8_t j;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_TWIST_SYM; i++) {
            c.setTwist(TwistS2R[i]);

            for (j = 0; j < CubeInfo::N_MOVES; j++) {
                CubieCube::CornMult(c, moveCube[j], d);
                TwistMove[i][j] = d.getTwistSym();
            }
        }
    }

    //UDSLice move table
    void initUDSliceMoveConj() {
        unsigned short i, udslice;
        uint8_t j, k;
        CubieCube c, d;

        for (i = 0; i < CubeInfo::N_SLICE; i++) {
            c.setUDSlice(i);

            for (j = 0; j < CubeInfo::N_MOVES; j += 3) {
                CubieCube::EdgeMult(c, moveCube[j], d);
                UDSliceMove[i][j] = d.getUDSlice();
            }

            for (j = 0; j < CubeInfo::SYM; j += 2) {
                EdgeConjugate(c, SymMultInv[0][j], d);
                UDSliceConj[i][j >> 1] = d.getUDSlice();
            }
        }

        for (i = 0; i < CubeInfo::N_SLICE; i++) {
            for (j = 0; j < CubeInfo::N_MOVES; j += 3) {
                udslice = UDSliceMove[i][j];

                for (k = 1; k < 3; k++) {
                    udslice = UDSliceMove[udslice][j];
                    UDSliceMove[i][j + k] = udslice;
                }
            }
        }
    }

    //init pruning
    void initAllPrun() {
        //MCPermPrun
        initRawSymPrun(
                MCPermPrun,
                MPermMove, MPermConj, CPermMove,
                nullptr, nullptr, nullptr,
                SymStatePerm, 0x8ea34,
                CubeInfo::N_MPERM * CubeInfo::N_PERM_SYM / 8 + 1,
                MCPP_IDX);

        //PermCombPPrun
        initRawSymPrun(
                EPermCCombPPrun,
                CCombPMove, CCombPConj, EPermMove,
                nullptr, nullptr, nullptr,
                SymStatePerm, 0x7d824,
                CubeInfo::N_COMB * CubeInfo::N_PERM_SYM / 8 + 1,
                PCPP_IDX);

        //SliceTwistPrun
        initRawSymPrun(
                UDSliceTwistPrun,
                nullptr, nullptr, nullptr,
                UDSliceMove, UDSliceConj, TwistMove,
                SymStateTwist, 0x69603,
                CubeInfo::N_SLICE * CubeInfo::N_TWIST_SYM / 8 + 1,
                STP_IDX);

        //SliceFlipPrun
        initRawSymPrun(
                UDSliceFlipPrun,
                nullptr, nullptr, nullptr,
                UDSliceMove, UDSliceConj, FlipMove,
                SymStateFlip, 0x69603,
                CubeInfo::N_SLICE * CubeInfo::N_FLIP_SYM / 8 + 1,
                SFP_IDX);

        //TwistFlipPrun
        initRawSymPrun(
                TwistFlipPrun,
                nullptr, nullptr, nullptr,
                nullptr, nullptr, TwistMove,
                SymStateTwist, 0x19603,
                CubeInfo::N_FLIP * CubeInfo::N_TWIST_SYM / 8 + 1,
                TFP_IDX);
    }

    //0 MCPermPrun
    //[N_MPERM][N_MOVES2] [N_MPERM][SYM] [N_PERM_SYM][N_MOVES2] u8 u8 u16 RawMove1, RawConj1, SymMoveVect1
    //1 PermCombPPrun
    //[N_COMB][N_MOVES2] [N_COMB][SYM] [N_PERM_SYM[N_MOVES2] u8 u8 u16 RawMove1, RawConj1, SymMoveVect1
    //2 SliceTwistPrun
    //[N_SLICE][N_MOVES] [N_SLICE][SYM_CLASSES] [N_TWIST_SYM][N_MOVES] u16 u16 u16 RawMove2, RawConj2, SymMoveVect2
    //3 SliceFlipPrun
    //[N_SLICE][N_MOVES] [N_SLICE][SYM_CLASSES] [N_PERM_SYM][N_MOVES] u16 u16 u16 RawMove2, RawConj2, SymMoveVect2
    //4 TwistFlipPrun
    //NO NO [N_TWIST_SYM][N_MOVES] u16 SymMoveVect2
    void initRawSymPrun(int PrunTable[],
                                               uint8_t RawMove1[][CubeInfo::N_MOVES2],
                                               uint8_t RawConj1[][CubeInfo::SYM],
                                               unsigned short SymMoveVect1[][CubeInfo::N_MOVES2],
                                               unsigned short RawMove2[][CubeInfo::N_MOVES],
                                               unsigned short RawConj2[][CubeInfo::SYM_CLASSES],
                                               unsigned short SymMoveVect2[][CubeInfo::N_MOVES],
                                               const unsigned short SymState[], int PrunFlag, int PrunTableSize,
                                               const CoordType &type) {

        const bool IS_TYPE_A = type < STP_IDX;
        const int8_t SYM_SHIFT = PrunFlag & 0xf;
        const int SYM_E2C_MAGIC_P = ((PrunFlag >> 4) & 1) == 1 ? SYM_E2C_MAGIC : 0x00000000;
        const bool IS_PHASE2 = ((PrunFlag >> 5) & 1) == 1;
        const int8_t INV_DEPTH = PrunFlag >> 8 & 0xf;
        const int8_t MAX_DEPTH = PrunFlag >> 12 & 0xf;

        const int8_t SYM_MASK = (1 << SYM_SHIFT) - 1;
        const bool ISTFP = type == TFP_IDX;
        const unsigned short N_RAW = ISTFP ? CubeInfo::N_FLIP : (type == MCPP_IDX ? CubeInfo::N_MPERM : (type == PCPP_IDX
                                                                                                  ? CubeInfo::N_COMB
                                                                                                  : CubeInfo::N_SLICE));
        const int N_SIZE = N_RAW * (type == MCPP_IDX || type == PCPP_IDX ? CubeInfo::N_PERM_SYM : type == SFP_IDX
                                                                                                      ? CubeInfo::N_FLIP_SYM
                                                                                                      : CubeInfo::N_TWIST_SYM);
        const int8_t N_MOVES = IS_PHASE2 ? CubeInfo::N_MOVES2 : CubeInfo::N_MOVES;
        const int NEXT_AXIS_MAGIC = IS_PHASE2 ? 0x42 : 0x92492;

        int mask, val, selArrMask, idx, idxx, i, m, done;
        int8_t check, xorVal, select, fsym, depth, prun;
        unsigned short flip, rawx, symx, symState;
        short raw, symmetry;
        uint8_t j;
        bool inv;


        for (i = 0; i < N_SIZE / 8 + 1; i++)
            PrunTable[i] = 0x11111111;

        setPruning(PrunTable, 0, 0 ^ 1);

        depth = 0;
        done = 1;

        while (depth < MAX_DEPTH) {
            mask = (depth + 1) * 0x11111111 ^ 0xffffffff;

            for (i = 0; i < PrunTableSize; i++) {
                val = PrunTable[i] ^ mask;
                val &= val >> 1;
                PrunTable[i] += val & (val >> 2) & 0x11111111;
            }

            inv = depth > INV_DEPTH;
            select = inv ? (depth + 2) : depth;
            selArrMask = select * 0x11111111;
            check = inv ? depth : (depth + 2);
            depth++;
            xorVal = depth ^ (depth + 1);
            val = 0;

            for (i = 0; i < N_SIZE; i++, val >>= 4) {
                if ((i & 7) == 0) {
                    val = PrunTable[i >> 3];

                    if (!hasZero(val ^ selArrMask)) {
                        i += 7;
                        continue;
                    }
                }

                if ((val & 0xf) != select)
                    continue;

                raw = i % N_RAW;
                symmetry = i / N_RAW;
                flip = 0;
                fsym = 0;

                if (ISTFP) {
                    flip = FlipR2S[raw];
                    fsym = flip & 7;
                    flip >>= 3;
                }

                for (m = 0; m < N_MOVES; m++) {
                    symx = IS_TYPE_A ? SymMoveVect1[symmetry][m] : SymMoveVect2[symmetry][m];

                    if (ISTFP)
                        rawx = FlipS2RF[
                                FlipMove[flip][Sym8Move[m << 3 | fsym]] ^
                                fsym ^ (symx & SYM_MASK)];
                    else
                        rawx = IS_TYPE_A ?
                               RawConj1[RawMove1[raw][m]][symx & SYM_MASK] :
                               RawConj2[RawMove2[raw][m]][symx & SYM_MASK];

                    symx >>= SYM_SHIFT;
                    idx = symx * N_RAW + rawx;
                    prun = getPruning(PrunTable, idx);

                    if (prun != check) {
                        if (prun < depth - 1)
                            m += NEXT_AXIS_MAGIC >> m & 3;
                        continue;
                    }

                    done++;

                    if (inv) {
                        setPruning(PrunTable, i, xorVal);
                        break;
                    }

                    setPruning(PrunTable, idx, xorVal);

                    for (j = 1, symState = SymState[symx]; (symState >>= 1) != 0; j++) {
                        if ((symState & 1) != 1)
                            continue;

                        idxx = symx * N_RAW;

                        if (ISTFP)
                            idxx += FlipS2RF[FlipR2S[rawx] ^ j];
                        else
                            idxx += IS_TYPE_A ? RawConj1[rawx][j ^ (SYM_E2C_MAGIC_P >> (j << 1) & 3)] :
                                    RawConj2[rawx][j ^ (SYM_E2C_MAGIC_P >> (j << 1) & 3)];

                        if (getPruning(PrunTable, idxx) == check) {
                            setPruning(PrunTable, idxx, xorVal);
                            done++;
                        }
                    }
                }
            }
        }
    }

    bool CoordCube::setWithPrun(const CubieCube &cc, int8_t depth) {
        CubieCube pc;
        twist = cc.getTwistSym();
        flip = cc.getFlipSym();
        tsym = twist & 7;
        twist = twist >> 3;

        prun = getPruning(TwistFlipPrun, twist << 11 | FlipS2RF[flip ^ tsym]);

        if (prun > depth)
            return false;

        fsym = flip & 7;
        flip = flip >> 3;

        slice = cc.getUDSlice();
        prun = std::max(prun, std::max(
                getPruning(UDSliceTwistPrun, twist * CubeInfo::N_SLICE + UDSliceConj[slice][tsym]),
                getPruning(UDSliceFlipPrun, flip * CubeInfo::N_SLICE + UDSliceConj[slice][fsym])));

        if (prun > depth)
            return false;

        CornConjugate(cc, 1, pc);
        EdgeConjugate(cc, 1, pc);
        twistc = pc.getTwistSym();
        flipc = pc.getFlipSym();

        prun = std::max(prun,
                        getPruning(TwistFlipPrun, (twistc >> 3) << 11 | FlipS2RF[flipc ^ (twistc & 7)]));

        return prun <= depth;
    }

    //move cube pruning
    int8_t CoordCube::doMovePrun(const CoordCube &cc, int8_t m) {
        slice = UDSliceMove[cc.slice][m];

        flip = FlipMove[cc.flip][Sym8Move[m << 3 | cc.fsym]];
        fsym = (flip & 7) ^ cc.fsym;
        flip >>= 3;

        twist = TwistMove[cc.twist][Sym8Move[m << 3 | cc.tsym]];
        tsym = (twist & 7) ^ cc.tsym;
        twist >>= 3;

        prun = std::max(
                std::max(
                        getPruning(UDSliceTwistPrun, twist * CubeInfo::N_SLICE + UDSliceConj[slice][tsym]),
                        getPruning(UDSliceFlipPrun, flip * CubeInfo::N_SLICE + UDSliceConj[slice][fsym])),
                getPruning(TwistFlipPrun, twist << 11 | FlipS2RF[flip << 3 | (fsym ^ tsym)]));

        return prun;
    }

    //move cube UDSliceSorted
    int8_t CoordCube::doMovePrunConj(const CoordCube &cc, int8_t m) {
        m = SymMove[3][m];
        flipc = FlipMove[cc.flipc >> 3][Sym8Move[m << 3 | cc.flipc & 7]] ^ (cc.flipc & 7);
        twistc = TwistMove[cc.twistc >> 3][Sym8Move[m << 3 | cc.twistc & 7]] ^ (cc.twistc & 7);

        return getPruning(TwistFlipPrun, (twistc >> 3) << 11 | FlipS2RF[flipc ^ (twistc & 7)]);
    }
} }