#include "Framework.h"
#include "PathFinder.h"
#include "TileMap.h"


PathFinder::PathFinder(TileMap* pTilemap)
{
	m_pTilemap = pTilemap;
	m_MapWidth = pTilemap->GetTileMapWidth();
	m_MapHeight = pTilemap->GetTileMapHeight();

	m_Nodes.resize(m_MapWidth * m_MapHeight);

}

PathFinder::~PathFinder()
{

}

bool PathFinder::FindPath(vec2 startpos, int ex, int ey)
{
    Reset();

    int StartingIndex = startpos.y * m_MapWidth + startpos.x;
    int DestIndex = ey * m_MapWidth + ex;

    m_Nodes[StartingIndex].cost = 0;
    m_Nodes[StartingIndex].finalCost = 0;
    m_Nodes[StartingIndex].status = PathNode::PathNodeStatus::Open;
    m_OpenNodes.push_back(StartingIndex);

    while (m_OpenNodes.size() > 0)
    {
        int currentNode = 99;
        int prevCost = 100;
        for (int i = 0; i < m_OpenNodes.size(); i++)
        {
            if (m_Nodes[m_OpenNodes[i]].finalCost < prevCost)
            {
                prevCost = m_Nodes[m_OpenNodes[i]].finalCost;
                currentNode = m_OpenNodes[i];
            }
        }    
        m_OpenNodes.erase(std::remove(m_OpenNodes.begin(), m_OpenNodes.end(), currentNode), m_OpenNodes.end());

        if (currentNode == DestIndex)
        {
            return true;
        }
        m_Nodes[currentNode].status = PathNode::PathNodeStatus::Closed;


        std::vector<int> NeighbourIndex = MakeListOfValidNeighbours(currentNode);


        for (int i = 0; i < NeighbourIndex.size(); i++)
        {

            if (m_Nodes[NeighbourIndex[i]].status == PathNode::PathNodeStatus::Unchecked)
            {
                m_Nodes[NeighbourIndex[i]].status = PathNode::PathNodeStatus::Open;
                m_OpenNodes.push_back(NeighbourIndex[i]);
            }

            int newCost = (m_Nodes[currentNode].cost + 1);

            if (newCost < m_Nodes[NeighbourIndex[i]].cost)
            {
                m_Nodes[NeighbourIndex[i]].parentNodeIndex = currentNode;
                //calc F,G,H
                m_Nodes[NeighbourIndex[i]].cost = newCost;
                m_Nodes[NeighbourIndex[i]].heuristic = (ex - startpos.x) + (ey - startpos.y);
                m_Nodes[NeighbourIndex[i]].finalCost = m_Nodes[NeighbourIndex[i]].cost + m_Nodes[NeighbourIndex[i]].heuristic;

            }

        }

    }

    return false;
}

//std::vector<int> PathFinder::GetPath(int ex, int ey)
int PathFinder::GetPath(int ex, int ey)
{
    int DestIndex = ey * m_MapWidth + ex;
    std::vector<int> path;
    int oldIndex = 99;
    int newIndex = 99;

    path.push_back(DestIndex);
    newIndex = m_Nodes[DestIndex].parentNodeIndex;
    oldIndex = m_Nodes[DestIndex].parentNodeIndex;
    path.push_back(newIndex);

    while (newIndex != -1)
    {
        newIndex = m_Nodes[oldIndex].parentNodeIndex;
        path.push_back(newIndex);
        oldIndex = newIndex;
    }
    path.pop_back();

    for (int i = 0; i < path.size() / 2; i++)
    {
        int temp = path[i];
        path[i] = path[(path.size() - i) - 1];
        path[(path.size() - i) - 1] = temp;
    }


    return path[0];
}



void PathFinder::Reset()
{
    for (int i = 0; i < m_Nodes.size(); i++)
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].cost = FLT_MAX;
        m_Nodes[i].finalCost = FLT_MAX;
        m_Nodes[i].heuristic = FLT_MAX;
        m_Nodes[i].status = PathNode::PathNodeStatus::Unchecked;
    }
}

std::vector<int> PathFinder::MakeListOfValidNeighbours(int tileIndex)
{
    std::vector<int> NeighbourIndex;
    for (int i = 0; i < 4; i++)
    {
        int currentPosX = 0;
        int currentPosY = 0;

        //left
        if (i == 0)
        {
            float Nindex = floor((tileIndex - 1) / m_MapWidth);
            float Tindex = floor(tileIndex / m_MapWidth);

            int fullIndex = (tileIndex - 1);
            if (fullIndex == -1)
                continue;
            currentPosX = int(fullIndex) % m_MapWidth;
            currentPosY = int(fullIndex) / m_MapWidth;

            if (m_Nodes[fullIndex].status != PathNode::PathNodeStatus::Closed && m_pTilemap->IsWalkableAtLocation(currentPosX, currentPosY))
            {
                if (Nindex == Tindex)
                {
                    NeighbourIndex.push_back(tileIndex - 1);
                }
            }
        }

        //Right
        if (i == 1)
        {
            float Nindex = floor((tileIndex + 1) / m_MapWidth);
            float Tindex = floor(tileIndex / m_MapWidth);

            int fullIndex = (tileIndex + 1);
            if (fullIndex == 100)
                continue;

            currentPosX = int(fullIndex) % m_MapWidth;
            currentPosY = int(fullIndex) / m_MapWidth;

            if (m_Nodes[fullIndex].status != PathNode::PathNodeStatus::Closed && m_pTilemap->IsWalkableAtLocation(currentPosX, currentPosY))
            {
                if (Nindex == Tindex)
                {
                    NeighbourIndex.push_back(tileIndex + 1);
                }
            }
        }

        //Down
        if (i == 2)
        {
            if (tileIndex >= 10)
            {
                int fullIndex = (tileIndex - 10);

                currentPosX = int(fullIndex) % m_MapWidth;
                currentPosY = int(fullIndex) / m_MapWidth;

                if (m_Nodes[fullIndex].status != PathNode::PathNodeStatus::Closed && m_pTilemap->IsWalkableAtLocation(currentPosX, currentPosY))
                {
                    NeighbourIndex.push_back(tileIndex - 10);
                }
            }
        }

        //Up
        if (i == 3)
        {
            if (tileIndex <= 89)
            {
                int fullIndex = (tileIndex + 10);

                currentPosX = int(fullIndex) % m_MapWidth;
                currentPosY = int(fullIndex) / m_MapWidth;

                if (m_Nodes[fullIndex].status != PathNode::PathNodeStatus::Closed && m_pTilemap->IsWalkableAtLocation(currentPosX, currentPosY))
                {
                    NeighbourIndex.push_back(tileIndex + 10);
                }
            }
        }
    }

    return NeighbourIndex;
}



//------------------------------ My Functions ------------------------------------------------------

