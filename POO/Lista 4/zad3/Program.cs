using System;
using System.Collections.Generic;

namespace zad3 
{
    public class Reusable
    {
        public void DoWork()
        {
            Console.WriteLine("Doing some work...");
        }
    }

    public class ObjectPool
    {
        private int _poolSize;
        private List<Reusable> _pool = new List<Reusable>();
        private List<Reusable> _acquired = new List<Reusable>();
        public static ObjectPool Instance { get; } = new ObjectPool(1);

        public ObjectPool(int poolSize)
        {
            if (poolSize <= 0)
            {
                throw new ArgumentException();
            }
            this._poolSize = poolSize;
        }

        public Reusable AcqureReusable()
        {
            if (_acquired.Count == this._poolSize)
            {
                throw new ArgumentException();
            }
            if (_pool.Count == 0)
            {
                var reusable = new Reusable();
                _pool.Add(reusable);
            }
            var element = _pool[0];
            _pool.Remove(element);
            _acquired.Add(element);
            return element;
        }

        public void ReleaseReusable(Reusable reusable)
        {
            if (!_acquired.Contains(reusable))
            {
                throw new ArgumentException();
            }
            _acquired.Remove(reusable);
            _pool.Add(reusable);
        }
    }

    public class BetterReusable
    {
        private Reusable _reusable;
        private bool _isReleased = false;

        public BetterReusable()
        {
            _reusable = ObjectPool.Instance.AcqureReusable();
        }

        public void Release()
        {
            if (_isReleased)
            {
                throw new InvalidOperationException("Object already released");
            }
            ObjectPool.Instance.ReleaseReusable(_reusable);
            _isReleased = true;
        }

        public void DoWork()
        {
            if (_isReleased)
            {
                throw new InvalidOperationException("Cannot use a released object");
            }
            _reusable.DoWork();
        }
    }
}


