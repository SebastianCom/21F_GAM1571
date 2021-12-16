#include "Framework.h"
#include "DataTypes.h"


#include <vector>

class TileMap;

struct PathNode
{
    enum class PathNodeStatus
    {
        Unchecked,
        Open,
        Closed,
    };

    int parentNodeIndex;
    PathNodeStatus status;

    float cost;      // Cost to get to this node.                       G
    float heuristic; // Heuristic: manhatten distance to destination.   H
    float finalCost; // Sum of the 2 values above.                      F
};

class PathFinder
{
public:
   
    PathFinder(TileMap* pTilemap);
    virtual ~PathFinder();

    // Start a search, supply the starting tile x,y and ending tile x,y.
    // Returns true if path found, false otherwise.
    bool FindPath(vec2 startpos, int ex, int ey);



    // Retrieve the final path.
    ///std::vector<int> GetPath(int ex, int ey);
    int GetPath(int ex, int ey);
    void Reset();
    
protected:
    
    TileMap* m_pTilemap;
    int m_MapWidth;
    int m_MapHeight;
    std::vector<int> m_OpenNodes;
    std::vector<PathNode> m_Nodes;
   
    std::vector<int> MakeListOfValidNeighbours(int tileIndex);

};
