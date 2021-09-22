#pragma once
#include "Common/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Template interface for zero arguments factories returning unique instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory>
    class IUniqueFactory
    {
    public:
        using FactoryType = TypeOfFactory;

    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUniqueFactory);
        IUniqueFactory() = default;
        virtual ~IUniqueFactory() = default;

        /**
         * @brief Creates new, unique instance of an object of type FactoryType.
         * 
         * @return 
         */
        virtual Unique<FactoryType> Create() const = 0;
    };

    /**
     * @brief Template interface for single arguments factories returning unique instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory, typename TypeOfParam>
    class IUniqueFactoryWithParam
    {
    public:
        using FactoryType = TypeOfFactory;
        using ParamType = TypeOfParam;

    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUniqueFactoryWithParam);
        IUniqueFactoryWithParam() = default;
        virtual ~IUniqueFactoryWithParam() = default;

        /**
         * @brief Creates new, unique instance of an object of type FactoryType using provided param.
         * 
         * @return 
         */
        virtual Unique<FactoryType> Create(ParamType param) const = 0;
    };

    /**
     * @brief Template interface for single arguments factories returning shared instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory, typename TypeOfParam>
    class ISharedFactoryWithParam
    {
    public:
        using FactoryType = TypeOfFactory;
        using ParamType = TypeOfParam;

    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(ISharedFactoryWithParam);
        ISharedFactoryWithParam() = default;
        virtual ~ISharedFactoryWithParam() = default;

        /**
         * @brief Creates new or returns existing, instance of an object of type FactoryType using provided param.
         * 
         * @return 
         */
        virtual Shared<FactoryType> Create(ParamType param) const = 0;
    };

    /**
     * @brief Class template automatically creating implementation of the IUniqueFactory interface template.
     * It provides a convenient way to create instance of the simple unique factory.
     * Given ConcreteType which instance will be created, must be a child of the given InterfaceType. Compile-time error is generated otherwise.
     */
    template<typename InterfaceType, typename ConcreteType>
    class AutomaticInterfaceFactory : public IUniqueFactory<InterfaceType>
    {
        static_assert(std::is_base_of_v<InterfaceType, ConcreteType>, "Provided ConcreteType does not inherit from InterfaceType");

    public:
        /**
         * @brief Creates new, unique instance of the ConcreteType object.
         * 
         * @return 
         */
        Unique<InterfaceType> Create() const override
        {
            return CreateUnique<ConcreteType>();
        }
    };
} // namespace CT_COMMON_NAMESPACE
