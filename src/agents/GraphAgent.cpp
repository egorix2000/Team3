#include <agents/GraphAgent.h>

GraphAgent::GraphAgent() {
    edgeCreationHelpers_.reserve(150);
    graph_.reserve(100);
}

GraphAgent::~GraphAgent() {
    for (int32_t i = 0; i < graph_.size(); ++i) {
        delete graph_[i];
    }
}

std::vector<Node*>& GraphAgent::getGraph() {
    return graph_;
}

Edge* GraphAgent::findEdge(uint32_t lineIdx) {
    return lineIdxToEdge_.at(lineIdx);
}

void GraphAgent::mapEdge(Edge* edge) {
    lineIdxToEdge_.insert(std::make_pair(edge->getLineIdx(), edge));
}

uint32_t GraphAgent::compressPointIdx(uint32_t idx) {
    return pointIdxCompression_.at(idx);
}