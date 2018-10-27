 #pragma once
#include "FileWriterInterface.h"
namespace tecplot { namespace ___3933 { class IntervalTree { UNCOPYABLE_CLASS(IntervalTree); public: typedef ___2090::SubzoneIndex_t TreeIndex_t; typedef std::vector<TreeIndex_t>    TreeIndexVector; static TreeIndex_t const BAD_TREE_INDEX = ___2090::INVALID_SUBZONE_OFFSET; static TreeIndex_t const MAX_TREE_INDEX = ___2090::MAX_SUBZONE_OFFSET; private: struct TreeNode { double      strikeValue; TreeIndex_t ___3681; TreeIndex_t size; TreeIndex_t left; TreeIndex_t right; ___372 operator==(TreeNode const& ___2888) const { return strikeValue == ___2888.strikeValue && ___3681 == ___2888.___3681 && size == ___2888.size && left == ___2888.left && right == ___2888.right; } }; TreeIndex_t m_root; TreeIndex_t m_numTreeNodes; std::vector<TreeNode> m_treeNodes; TreeIndex_t m_maxNumIntervalsReserved; TreeIndex_t m_curNumIntervals; std::vector<double> m_minimums; std::vector<double> m_maximums; TreeIndex_t m_numAlDhEntries; TreeIndexVector m_alEntries; TreeIndexVector m_dhEntries; double medianOfVector(std::vector<double>& arrayValues, TreeIndex_t ___2795); TreeIndex_t constructNode(TreeIndexVector const& list, TreeIndex_t ___2812); void queryNode(TreeIndex_t nodeOffset, double ___4314, TreeIndexVector& intervalList); ___372 minAscendingCompare(TreeIndex_t i, TreeIndex_t ___2105); ___372 maxDescendingCompare(TreeIndex_t i, TreeIndex_t ___2105); static ___372 encodeAsciiTreeNodeValue(char*           str, TreeNode const& treeNode); ___372 ___4550( FileWriterInterface& file, char const*          ___972, ___4636          ___1251); ___372 ___4479( FileWriterInterface& file, char const*          ___972, ___4636          ___1251); ___372 ___4505( FileWriterInterface& file, char const*          ___972, ___4636          ___1251); public: IntervalTree() : m_root(BAD_TREE_INDEX) , m_numTreeNodes(0) , m_maxNumIntervalsReserved(0) , m_curNumIntervals(0) , m_numAlDhEntries(0) {} ~IntervalTree() {} ___372 addInterval(double minValue, double maxValue); ___372 addIntervalsMinMaxArray(TreeIndex_t numMinMaxes, ___2481 const& arrayMinMaxes); void queryIntervals(double ___4314, TreeIndexVector& intervalList); ___372 constructTree(); ___372 writeTreeToFile( FileWriterInterface& file, ___1172           zone); ___372 readTreeFromFile(FileWriterInterface& file); }; }}
