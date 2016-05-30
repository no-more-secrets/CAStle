#include <stdexcept>
#include <stack>
#include "Parser.hpp"
#include "Templates.hpp"

namespace DS          {
namespace CAS         {
namespace Expressions {

Parser::Parser(std::shared_ptr<Tokens::ScannerBuilder> _sBuilder, std::shared_ptr<Expressions::Builder> _eBuilder,
               std::shared_ptr<Numbers::NumberFormatter> _nFormatter, std::shared_ptr<Tokens::Tokenizer> _tokenizer)
{
    eBuilder     = _eBuilder;
    nFormatter     = _nFormatter;
    sBuilder     = _sBuilder;
    tokenizer     = _tokenizer;
}

Expression::Ptr Parser::parse(const std::string& source)
{
    if (scanners.empty())
        buildScanners(scanners, sBuilder);
    std::vector<Token> tokens;
    stopLocation = source.begin();
    bool success = tokenizer->tokenizePriority(source, scanners, tokens);
    if (!success)
    {
        stopLocation = tokenizer->getStopLocation();
        return Expression::Ptr();
    }
    std::vector<Command> commands;
    if (!parseTokens(tokens, commands))
        return Expression::Ptr();
    for (std::vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        //cout << endl << (*it).getNodeName() << ",  " << (*it).getNodeType() << ",  " << (*it).getNumberOfChildren();
    }
    return buildExpression(commands);
}

Expression::Ptr Parser::buildExpression(const std::vector<Command>& commands)
{
    stack<Expression::Ptr> expStack;
    Expression::Ptr node, nullShared;
    Numbers::Number* number;
    std::vector<Expression::Ptr> children;

    for (std::vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        switch ((*it).getNodeType())
        {
        case Command::literal:
            number = nFormatter->format((*it).getNodeName());
            if (!number)
                return nullShared;
            node = eBuilder->literal(number);
            expStack.push(node);
            break;
        case Command::symbol:
            for (unsigned int i = 0; i < (*it).getNumberOfChildren(); i++)
            {
                if (expStack.size() == 0)
                    return Expression::Ptr();
                children.insert(children.begin(), getPop(expStack));
            }
            node = eBuilder->operator()((*it).getNodeName(), children);
            if (!node)
                return nullShared;
            expStack.push(node);
            children.resize(0);
            break;
        default:
            throw std::invalid_argument("invalid node type in Expressions::Parser::buildExpressions(std::vector<Command>)");
        }
    }
    if (expStack.size() != 1)
        return nullShared;

    return expStack.top();
}

} /* namespace Expressions */
} /* namespace CAS */
} /* namespace DS */