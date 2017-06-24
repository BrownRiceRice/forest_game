#ifndef AvailableParameters_h
#define AvailableParameters_h

namespace ParamWorld {
	enum AvailableParameters {
		// Colors
		SP_Red,
		SP_Green,
		SP_Blue,
		SP_Alpha,

		// Tree Variables
		SP_Depth,
		SP_Width,
		SP_Height,
		SP_Scale,
		SP_SplitAngle,
		SP_BranchR,
		SP_BranchG,
		SP_BranchB,
		SP_LeafR,
		SP_LeafG,
		SP_LeafB,
		SP_LeafSize,

		// Rock Variables
		SP_Rock_Depth,
		SP_Rock_R,
		SP_Rock_G,
		SP_Rock_B,
		SP_Rock_HeightMult,

		// Total number of variables
		SP_Count
	};
}

#endif
